// Fill out your copyright notice in the Description page of Project Settings.

#include "Murakha.h"


// Sets default values
AMurakha::AMurakha()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

TArray<APawn*> AMurakha::ScanForPawns()
{
	TArray<APawn*> Pawns;


	return Pawns;

}

// Called when the game starts or when spawned
void AMurakha::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMurakha::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMurakha::UpdateLocation()
{
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

