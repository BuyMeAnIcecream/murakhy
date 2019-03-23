// Fill out your copyright notice in the Description page of Project Settings.
#include "TerraFormer.h"
#include "Engine/World.h"
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

ETileType ATerraFormer::TopTypeOfNeighbors(int tileX, int tileY)
{
	TArray<int> times;

	times.Init(0, (int)ETileType::ET_END);

	for (int i = tileY - 1; i < tileY + 2; ++i) 
	{
		for (int j = tileX - 1; j < tileX + 2 ; ++j)
		{
			if (i >= 0 && 
				j >= 0 &&
				i < Height &&
				j < Width)
			{
				if (tileX == j && tileY == i)
				{
					continue;
				}
//				UE_LOG(YourLog, Warning, TEXT("times met %d"), times[i]);
				ETileType currentType = Tiles[i][j]->TileType;
				times[(int)currentType] = times[(int)currentType] + 1;
//				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("X  = %d Y = %d"), j, i));	
			}
		}
	}

	//this should be a map for sure
	int mostTimesIndex = 0;
	int mostTimes = 0;
	for (int i = 0; i < times.Num(); i++) {
		//don't care what it returns if there are 2 or more equal results
		if (mostTimes < times[i])
		{
			mostTimes = times[i];
			mostTimesIndex = i;
		}
//		UE_LOG(YourLog, Warning, TEXT("times met %d"), times[i]);
		
	}
	return (ETileType)mostTimesIndex;
}

void ATerraFormer::TerraForm()
{
	if (!Tile)
	{
		return;
	}
	UWorld* const World = GetWorld();
	if (World)
	{
		for (int y = 0; y < Height; y++)
		{
			Tiles.Add(FTile2DArray());
			for (int x = 0; x < Width; x++)
			{
				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

				ATile* NewTile = GetWorld()->SpawnActor<ATile>(Tile, FVector(x * 200, y * 200, 0), FRotator(0, 0, 0), ActorSpawnParams);
				NewTile->TileType = RandomizeFromMap();
				NewTile->UpdateMaterial();
				Tiles[y].Add(NewTile);
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
//			GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Red, FString::Printf(TEXT("current Like:  %f tile sorted number %d tile like: %f, rand val: %f"), currentLikelihood, (int)Elem.Key, Elem.Value, randValue));
			return Elem.Key;
		}
		
	}
//	GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Red, FString::Printf(TEXT("returning default")));
	return ETileType::ET_Desert;
}



void ATerraFormer::Smooth()
{
	//todo dynamic array
	ETileType NewTileTypes[20][20];
	float offset = 10000;
	for (int y = 0; y < Height; y++)
	{
		for (int x = 0; x < Width; x++)
		{
			NewTileTypes[y][x] = TopTypeOfNeighbors(x, y);
		}
	}

	for (int y = 0; y < Height; y++)
	{
		for (int x = 0; x < Width; x++)
		{
			Tiles[y][x]->TileType = NewTileTypes[y][x];
			Tiles[y][x]->UpdateMaterial();
		}
	}
}


