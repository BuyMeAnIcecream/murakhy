// Fill out your copyright notice in the Description page of Project Settings.

#include "GridMap.h"
#include "Murakha.h"
//#include "Tile.h"
#include "Locatable.h"


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

}

bool AGridMap::IsTileStepable(int x, int y)
{
	//TODO add check if can fit
		return  x >= 0 &&
			y >= 0 &&
			x < GridWidth &&
			y < GridHeight;
}

ATile * AGridMap::GetTile(int x, int y)
{
	if (!IsTileStepable(x, y) || !Tiles[y][x])
	{
		return nullptr;
	}
	return Tiles[y][x];
}

ATile * AGridMap::GetTile(FIntPoint Location)
{
	if (!IsTileStepable(Location.X, Location.Y) || !Tiles[Location.Y][Location.X])
	{
		return nullptr;
	}
	return Tiles[Location.Y][Location.X];
}

APawn* AGridMap::SpawnMurakha(FIntPoint Location)
{
	APawn* Spawn = nullptr;
	if (PawnToSpawn)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		Spawn = GetWorld()->SpawnActor<APawn>(PawnToSpawn, SpawnParams);		//TODO save to game manager to call updates
	
		ILocatable* Locatable = Cast<ILocatable>(Spawn);
		if (Locatable)
		{
			//Don't call your functions directly, use the 'Execute_' prefix
			//the Execute_ReactToHighNoon and Execute_ReactToMidnight are generated on compile
			//you may need to compile before these functions will appear
			Locatable->Execute_SetGridLocation(Cast<UObject>(Locatable),Location);
			Locatable->Execute_UpdateLocation(Cast<UObject>(Locatable));
		}
		
		AMurakha *SpawnedMurakha = Cast<AMurakha>(Spawn);
		if (SpawnedMurakha)
		{
			UE_LOG(LogTemp, Warning, TEXT("gridmap added"));
			SpawnedMurakha->GridMap = this;
			SpawnedMurakha->LocatedOn = GetTile(Location);
			
		}
		
	}
	return Spawn;
}



ETileType AGridMap::TopTypeOfNeighbors(int tileX, int tileY)
{
	TArray<int> times;

	times.Init(0, (int)ETileType::ET_END);

	for (int i = tileY - 1; i < tileY + 2; ++i)
	{
		for (int j = tileX - 1; j < tileX + 2; ++j)
		{
			if (i >= 0 &&
				j >= 0 &&
				i < GridHeight &&
				j < GridWidth)
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
