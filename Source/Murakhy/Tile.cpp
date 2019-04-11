// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetMobility(EComponentMobility::Movable);
	
	IsBusy = false;
	//Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
}

void ATile::UpdateMaterial()
{
	UMaterial* mat = *MaterialMap.Find(TileType);
	if (mat)
	{
		Mesh->SetMaterial(0, mat);
	}

}
void ATile::MovedOff()
{
	MurakhaOnTile = nullptr;
	IsBusy = false;
}

void ATile::MovedOn(AMurakha * Murakha)
{
	MurakhaOnTile = Murakha;
	IsBusy = true;
}
/*
void ATile::AddLocatable(TScriptInterface<ILocatable> *Locatable)
{
	StoredLocatables.Add(Locatable);
}

void ATile::RemoveLocatable(TScriptInterface<ILocatable> *Locatable)
{
	StoredLocatables.Remove(Locatable);
}

*/