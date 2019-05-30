// Fill out your copyright notice in the Description page of Project Settings.

#include "TurnManager.h"
#include "Updatable.h"

// Sets default values
ATurnManager::ATurnManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATurnManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATurnManager::NextTurn() const
{
	for (auto&& Element : Updatables)
	{
		IUpdatable* InterfacePtr = CastChecked<IUpdatable>(Element);
		if (InterfacePtr)
		{
			InterfacePtr->Execute_UpdateOnTurn(Cast<UObject>(InterfacePtr));
		}
	}
}

void ATurnManager::AddUpdatable(UObject* ToAdd)
{
	IUpdatable* Updatable = Cast<IUpdatable>(ToAdd); 	//I feel really bad about this
	if (Updatable)
	{
		Updatables.Add(ToAdd);
	}
}

void ATurnManager::RemoveUpdatable(UObject* ToRemove)
{
	IUpdatable* Updatable = Cast<IUpdatable>(ToRemove);
	if (Updatable)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s removed from updatables"), *GetNameSafe(ToRemove));
		Updatables.Remove(ToRemove);
	}
}

