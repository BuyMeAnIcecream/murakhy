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
		UE_LOG(LogTemp, Warning, TEXT("Turn Manager Found"));
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


void AGridMap::GetNeighborsOf(TArray<ATile*>& Out, FIntPoint TileLoc, uint8 Radius)
{
	for (int i = TileLoc.Y - Radius; i < TileLoc.Y + Radius + 1; ++i)
	{
		for (int j = TileLoc.X - Radius; j < TileLoc.X + Radius + 1; ++j)
		{
			if (TileLoc.X == j && TileLoc.Y == i)
			{
				continue;
			}
			ATile* CurrentTile = GetTile(i, j);
			if (CurrentTile)
			{
				Out.Add(CurrentTile);
			}
		}
	}
}

EDirection AGridMap::CoordinatesToDirection(FIntPoint Coord)
{
	if (Coord.X == 0 && Coord.Y < 0)
	{
		return EDirection::ET_North;
	}

	if(Coord.X > 0 && Coord.Y < 0)
	{
		return EDirection::ET_NorthEast;
	}

	if (Coord.X > 0 && Coord.Y == 0)
	{
		return EDirection::ET_East;
	}

	if (Coord.X > 0 && Coord.Y > 0)
	{
		return EDirection::ET_SouthEast;
	}

	if (Coord.X == 0 && Coord.Y > 0)
	{
		return EDirection::ET_South;
	}

	if (Coord.X < 0 && Coord.Y > 0)
	{
		return EDirection::ET_SouthWest;
	}

	if (Coord.X < 0 && Coord.Y == 0)
	{
		return EDirection::ET_West;
	}

	if (Coord.X < 0 && Coord.Y < 0)
	{
		return EDirection::ET_NorthWest;
	}

return EDirection::ET_END;
}


FIntPoint AGridMap::DirectionToCoordinates(EDirection Dir)
{
	int X = 0;
	int Y = 0;

	switch (Dir)
	{
	case EDirection::ET_North:
		Y = -1;
		break;

	case EDirection::ET_NorthEast:
		X = 1;
		Y = -1;
		break;

	case EDirection::ET_East:
		X = 1;
		break;

	case EDirection::ET_SouthEast:
		X = 1;
		Y = 1;
		break;

	case EDirection::ET_South:
		Y = 1;
		break;

	case EDirection::ET_SouthWest:
		X = -1;
		Y = 1;
		break;

	case EDirection::ET_West:
		X = -1;
		break;

	case EDirection::ET_NorthWest:
		X = -1;
		Y = -1;
		break;

	default:
		break;
	}

	return FIntPoint(X, Y);
}

APawn* AGridMap::SpawnMurakha(const FIntPoint Location)
{
	APawn* Spawn = nullptr;
	if (PawnToSpawn)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		
		//TODO check if tile is free
		Spawn = GetWorld()->SpawnActor<APawn>(PawnToSpawn, SpawnParams);		//TODO save to turn manager to call updates
	
		AMurakha *SpawnedMurakha = Cast<AMurakha>(Spawn);
		if (SpawnedMurakha)
		{
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

	Times.Init(0, int(ETileType::ET_End));

	for (int i = TileY - 1; i < TileY + 2; ++i)
	{
		for (int j = TileX - 1; j < TileX + 2; ++j)
		{
			if (IsInBounds(i,j))
			{
				if (TileX == j && TileY == i)
				{
					continue;
				}
				//				UE_LOG(YourLog, Warning, TEXT("times met %d"), times[i]);
				ETileType CurrentType = Tiles[i][j]->TileType;
				Times[int(CurrentType)] = Times[int(CurrentType)] + 1;
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
	return ETileType(mostTimesIndex);
}


