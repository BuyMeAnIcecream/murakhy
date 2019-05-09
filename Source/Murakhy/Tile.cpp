// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Murakha.h"

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
    //TODO fix dis. add a bunch of them manually and store the references.

}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < int(EBioParameter::EBP_END); i++)
	{
		ConsumableStored.Add(EBioParameter(i), 0);
	}

	TArray<UActorComponent*> TempMesh = GetComponentsByTag(UStaticMeshComponent::StaticClass(),TEXT("Visual"));
	for (auto& AComp : TempMesh)
	{
		UStaticMeshComponent* Mesh = Cast<UStaticMeshComponent>(AComp);
		if(Mesh)
		{
			Meshes.Add(Mesh);
		}
	}

	TArray<UActorComponent*> TempScene = GetComponentsByTag(USceneComponent::StaticClass(), TEXT("Visual"));
	for(auto& AScene: TempScene)
	{
		USceneComponent* SceneComp = Cast<USceneComponent>(AScene);
		if (SceneComp)
		{
			VisualSockets.Add(SceneComp);
			UE_LOG(LogTemp, Warning, TEXT("SceneComp %s"), *GetNameSafe(SceneComp));
		}
	}
}

void ATile::UpdateMaterial()
{
	UMaterial* mat = *MaterialMap.Find(TileType);
	if (mat)
	{
		Mesh->SetMaterial(0, mat);
	}
}

void ATile::OnTileTypeUpdated()
{
	for (int i = 0; i < int(EBioParameter::EBP_END); i++) 	//removing all the previously stored stuff
	{
		ConsumableStored[EBioParameter(i)] = 0;
	}

	UpdateMaterial(); 
}

void ATile::ProduceConsumable()
{
	if (!ConsumableInfo.Contains(TileType))
	{
		return;
	}

	const FConsumableData ConsData = ConsumableInfo[TileType];
	
	if(ConsumableStored[ConsumableInfo[TileType].TypeProduced] < ConsData.ConsumableMax)
	{
		ConsumableStored[ConsumableInfo[TileType].TypeProduced] += ConsData.AmountProducedPerTurn + FMath::RandRange(0, ConsData.RandomExtraProducedPerTurn);
		if (ConsumableStored[ConsumableInfo[TileType].TypeProduced] > ConsData.ConsumableMax)
		{
			ConsumableStored[ConsumableInfo[TileType].TypeProduced] = ConsData.ConsumableMax;
		}
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

void ATile::UpdateVisuals()
{
	int nextSocketIndex = 0; //free socket
	for(int i = 0; i < int(EBioParameter::EBP_END); i++)
	{

		if(VisualSockets.IsValidIndex(nextSocketIndex) && Meshes.IsValidIndex(i))
		{
			if (ConsumableStored[EBioParameter(i)] <= 0)
			{
				Meshes[i]->SetVisibility(false);
				continue;
			}
			Meshes[i]->SetWorldLocation(VisualSockets[nextSocketIndex]->GetComponentLocation());
			Meshes[i]->SetVisibility(true);
			nextSocketIndex++;
		}
	}
}

void ATile::UpdateOnTurn_Implementation()
{
	ProduceConsumable();
	UpdateVisuals();
}

uint8 ATile::ConsumeOff(EBioParameter Consumable, uint8 Amount)
{
	uint8 Consumed = 0;
	if(ConsumableStored[Consumable] < Amount)
	{
		Consumed = ConsumableStored[Consumable];
		ConsumableStored[Consumable] = 0;
	}
	else
	{
		ConsumableStored[Consumable] -= Amount;
		Consumed = Amount;
	}
	return Consumed;
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