// Fill out your copyright notice in the Description page of Project Settings.

#include "Murakha.h"
#include "Tile.h"
#include "GridMap.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"

// Sets default values
AMurakha::AMurakha()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetMobility(EComponentMobility::Movable);
}

TArray<APawn*> AMurakha::ScanForPawns()
{
	TArray<APawn*> Pawns;


	return Pawns;

}

void AMurakha::Move(EDirection Direction)
{
	if (!GridMap)
	{
		UE_LOG(LogTemp, Warning, TEXT("no GridMap assigned"));
		return;
	}

	ATile* SteppingOn = nullptr;
	switch (Direction)
	{
	case EDirection::ET_North:
		if (GridMap->IsTileStepable(GridLocation.X, GridLocation.Y - 1))
		{
			GridLocation = FIntPoint(GridLocation.X, GridLocation.Y - 1);
			SteppingOn = GridMap->GetTile(GridLocation);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("terrain not stepable"));
		}
		break;
	case EDirection::ET_East:
		if (GridMap->IsTileStepable(GridLocation.X + 1, GridLocation.Y))
		{
			GridLocation = FIntPoint(GridLocation.X + 1, GridLocation.Y);
			SteppingOn = GridMap->GetTile(GridLocation);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("terrain not stepable")); 
		}
		break;
	case EDirection::ET_South:
		if (GridMap->IsTileStepable(GridLocation.X, GridLocation.Y + 1))
		{
			GridLocation = FIntPoint(GridLocation.X, GridLocation.Y + 1);
			SteppingOn = GridMap->GetTile(GridLocation);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("terrain not stepable"));
		}
		break;
	case EDirection::ET_West:
		if (GridMap->IsTileStepable(GridLocation.X - 1, GridLocation.Y))
		{
			GridLocation = FIntPoint(GridLocation.X - 1, GridLocation.Y);
			SteppingOn = GridMap->GetTile(GridLocation);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("terrain not stepable"));
		}
		break;
	default:
		break;
	}
	if (SteppingOn)
	{
		if (SteppingOn->IsBusy)
		{
			UE_LOG(LogTemp, Warning, TEXT("tile is busy"));
			return;
		}
		if (LocatedOn)
		{
			LocatedOn->MovedOff();
		}
		//TODO SteppingOn->RemoveLocatable;
		LocatedOn = SteppingOn;
		LocatedOn->MovedOn(this);
			
	}
	UpdateLocation_Implementation();
}

// Called when the game starts or when spawned
void AMurakha::BeginPlay()
{
	Super::BeginPlay();
}




void AMurakha::UpdateLocation_Implementation()
{
//	LocatedOn = //get new tile from map. here..?
	if (LocatedOn)
	{
		//TODO add capsule and add it's half height
		SetActorLocation(FVector(0,0, 200) + LocatedOn->GetActorLocation());	
		//LocatedOn->AddLocatable();
	}
	
	//map->getTile();
	//LocatedOn = 
}

FIntPoint AMurakha::GetGridLocation_Implementation()
{
	return GridLocation;
}

void AMurakha::SetGridLocation_Implementation(FIntPoint NewLoc)
{
	GridLocation = NewLoc;
}

// Called to bind functionality to input
//void AMurakha::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//}

