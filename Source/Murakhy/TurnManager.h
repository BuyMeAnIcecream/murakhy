// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TurnManager.generated.h"

UCLASS()
class MURAKHY_API ATurnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurnManager();
	
	UFUNCTION(BlueprintCallable, Category = Updatables)
	void AddUpdatable(UObject* ToAdd);

	UFUNCTION(BlueprintCallable, Category = Updatables)
	void RemoveUpdatable(UObject* ToRemove);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable, Category = Turn)
	void NextTurn() const;

	//I refuse to believe this is the right way to do it but funny errors I got from storing TScript pointers made me..
	UPROPERTY(VisibleAnywhere, Category = Turn)
	TArray<UObject*> Updatables;
};
