// Fill out your copyright notice in the Description page of Project Settings.

#include "GridMap.h"
#include "Murakha.h"
//#include "Tile.h"
#include "Locatable.h"
#include "MurakhyAIController.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AGridMap::AGridMap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AGridMap::BeginPlay()
{
	Super::BeginPlay();

	//Find TM
	TArray<AActor*> Found;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATurnManager::StaticClass(), Found);
	ATurnManager* TM = Cast<ATurnManager>(Found.Pop());
	if(TM)
	{
		TurnManager = TM;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Turn Manager Not Found"));
	}
	
}

bool AGridMap::IsInBounds(const int x, const int y) const
{
	//TODO add check if can fit
		return  x >= 0 &&
			y >= 0 &&
			x < GridWidth &&
			y < GridHeight;
}

ATile * AGridMap::GetTile(const int x, const int y)
{
	if (!IsInBounds(x, y) || !Tiles[y][x])
	{
		return nullptr;
	}
	return Tiles[y][x];
}

ATile * AGridMap::GetTile(const FIntPoint Location)
{
	if (!IsInBounds(Location.X, Location.Y) || !Tiles[Location.Y][Location.X])
	{
		return nullptr;
	}
	return Tiles[Location.Y][Location.X];
}

APawn* AGridMap::SpawnMurakha(const FIntPoint Location)
{
	APawn* Spawn = nullptr;
	if (PawnToSpawn)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		Spawn = GetWorld()->SpawnActor<APawn>(PawnToSpawn, SpawnParams);		//TODO save to turn manager to call updates
	
		AMurakha *SpawnedMurakha = Cast<AMurakha>(Spawn);
		if (SpawnedMurakha)
		{
			UE_LOG(LogTemp, Warning, TEXT("gridmap added"));
			SpawnedMurakha->GridMap = this;
			SpawnedMurakha->LocatedOn = GetTile(Location);

			ILocatable* Locatable = Cast<ILocatable>(Spawn);
			if (Locatable)
			{
				Locatable->Execute_SetGridLocation(Cast<UObject>(Locatable), Location);
				Locatable->Execute_UpdateLocation(Cast<UObject>(Locatable));
			}

			AMurakhyAIController *AIController = Cast<AMurakhyAIController>(SpawnedMurakha->GetController());
			if(AIController)
			{
				if(TurnManager)
				{
					TurnManager->AddUpdatable(AIController);
				}
			}
		}
	}
	return Spawn;
}



ETileType AGridMap::TopTypeOfNeighbors(int TileX, int TileY)
{
	TArray<int> Times;

	Times.Init(0, (int)ETileType::ET_End);

	for (int i = TileY - 1; i < TileY + 2; ++i)
	{
		for (int j = TileX - 1; j < TileX + 2; ++j)
		{
			if (i >= 0 &&
				j >= 0 &&
				i < GridHeight &&
				j < GridWidth)
			{
				if (TileX == j && TileY == i)
				{
					continue;
				}
				//				UE_LOG(YourLog, Warning, TEXT("times met %d"), times[i]);
				ETileType CurrentType = Tiles[i][j]->TileType;
				Times[(int)CurrentType] = Times[(int)CurrentType] + 1;
				//				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("X  = %d Y = %d"), j, i));	
			}
		}
	}

	//this should be a map for sure
	int mostTimesIndex = 0;
	int mostTimes = 0;
	for (int i = 0; i < Times.Num(); i++) {
		//don't care what it returns if there are 2 or more equal results
		if (mostTimes < Times[i])
		{
			mostTimes = Times[i];
			mostTimesIndex = i;
		}
		//		UE_LOG(YourLog, Warning, TEXT("times met %d"), times[i]);

	}
	return (ETileType)mostTimesIndex;
}
