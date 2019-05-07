// Fill out your copyright notice in the Description page of Project Settings.
#include "TerraFormer.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"

// Sets default values
ATerraFormer::ATerraFormer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATerraFormer::BeginPlay()
{
	Super::BeginPlay();
}



void ATerraFormer::TerraForm()
{
	if (!Tile)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tile not assigned"));
		return;
	}
	UWorld* const World = GetWorld();
	if (World)
	{
		if (!MapToSpawn)
		{
			UE_LOG(LogTemp, Warning, TEXT("MapToSpawn not assigned"));
			return;
		}
		
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(World, AGridMap::StaticClass(), FoundActors);
		if (FoundActors.IsValidIndex(0))
		{
			AGridMap* FoundMap = Cast<AGridMap>(FoundActors[0]);
			if (FoundMap)
			{
				GridMap = FoundMap;
				GridMap->GridHeight = Height;
				GridMap->GridWidth = Width;
				UE_LOG(LogTemp, Warning, TEXT("Map found"));
			}
		}
		else
		{
			FActorSpawnParameters MapSpawnParams;
			MapSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			GridMap = World->SpawnActor<AGridMap>(MapToSpawn, MapSpawnParams);
			GridMap->GridHeight = Height;
			GridMap->GridWidth = Width;
			UE_LOG(LogTemp, Warning, TEXT("Map spawned"));
		}

		
		for (int y = 0; y < Height; y++)
		{
			GridMap->Tiles.Add(FTile2DArray());
			for (int x = 0; x < Width; x++)
			{
				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

				ATile* NewTile = GetWorld()->SpawnActor<ATile>(Tile, FVector(x * 200, y * 200, 0), FRotator(0, 0, 0), ActorSpawnParams);
				
				NewTile->LocationOnMap.X = x;
				NewTile->LocationOnMap.Y = y;
				
				NewTile->TileType = RandomizeFromMap();
				NewTile->OnTileTypeUpdated();
				GridMap->Tiles[y].Add(NewTile);
				//add to updatable array
				if (TurnManager)
				{ 
					TurnManager->AddUpdatable(NewTile);
				}
			}
		}
	}
}
//TODO pass sorted map
ETileType ATerraFormer::RandomizeFromMap()
{
	float randValue = FMath::RandRange(0.f, 1.f);
	//TODO move sorting out of function to exclude from loop of terraforming. pass sorted map as argument
	LikelihoodMap.ValueSort([](float A, float B) {
		return A > B; // sort values 
	});

	//this is some kinda assembly bullsh
	float currentLikelihood = 0.f;
	for(auto& Elem: LikelihoodMap)
	{
		currentLikelihood += Elem.Value;
		if (randValue < currentLikelihood)
		{
			return Elem.Key;
		}
	}
	GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Red, FString::Printf(TEXT("default tile")));
	return ETileType::ET_Desert;
}



void ATerraFormer::Smooth() const
{
	//TODO dynamic array
	ETileType NewTileTypes[20][20];
	for (int y = 0; y < Height; y++)
	{
		for (int x = 0; x < Width; x++)
		{
			NewTileTypes[y][x] = GridMap->TopTypeOfNeighbors(x, y);
		}
	}

	for (int y = 0; y < Height; y++)
	{
		for (int x = 0; x < Width; x++)
		{
			GridMap->Tiles[y][x]->TileType = NewTileTypes[y][x];
			GridMap->Tiles[y][x]->OnTileTypeUpdated();
		}
	}
}


