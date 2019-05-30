// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Locatable.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "EBioParameter.h"
#include "EDirection.h"
#include "Updatable.h"
//Normal Forward Declaration
class AGridMap;
class ATurnManager;
#include "Murakha.generated.h"



USTRUCT(BlueprintType)
struct FParamValues
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Category = Data)
	uint8 Max;
	
	UPROPERTY(EditDefaultsOnly, Category = Data)
	uint8 Sufficient;
	
	UPROPERTY(EditDefaultsOnly, Category = Data)
	uint8 ConsumesInTurn;
};
	

UCLASS()
class MURAKHY_API AMurakha : public APawn, public ILocatable, public IUpdatable
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMurakha();

//	UPROPERTY(EditAnywhere, Category = "Location")

	UPROPERTY(EditAnywhere, Category = "Behavior")
	class UBehaviorTree *Behavior;

	UFUNCTION(BlueprintCallable, Category = "Search")
	static TArray<APawn*> ScanForPawns();

	UPROPERTY(VisibleAnywhere, Category = "Location")
	class ATile* LocatedOn;
	
	UPROPERTY(VisibleAnywhere, Category = "Location")
	AGridMap* GridMap;
	
	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool Move(EDirection Direction);

	UFUNCTION(BlueprintCallable, Category = "Consume")
	void Consume(EBioParameter BioParam, ATile *ConsumeOff);

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	UStaticMeshComponent *Mesh;

	UPROPERTY(BlueprintReadOnly, Category = "Root")
	USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly, Category = "Data")
		TMap <EBioParameter, FParamValues> BioParams;

	UPROPERTY(VisibleAnywhere, Category = "BioParameters")
		TMap <EBioParameter, uint8> CurrentBioParam;

	UPROPERTY(EditDefaultsOnly, Category = "LifeSpan")
		int LifeSpan;

	UPROPERTY(EditDefaultsOnly, Category = "LifeSpan")
		int RandomDeviation;

	UPROPERTY(VisibleAnywhere, Category = "LifeSpan")
		int CurrentAge = 0;

	UPROPERTY(VisibleInstanceOnly, Category = "LifeSpan")
		int DiesAt;

	UFUNCTION(BlueprintCallable, Category = "Lifespan")
		void Age();

	UPROPERTY(VisibleInstanceOnly, Category = "TurnManager")
		ATurnManager* TurnManager;
/*
	UFUNCTION(BlueprintCallable, Category = "Consume")
		void Consume(EBioParameter BioParam, uint8 &Available);
*/

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FIntPoint GridLocation;
public:	

	
//	UFUNCTION(BlueprintCallable, Category = "Location")
//	void UpdateLocation();
	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GridLocation")
		FIntPoint GetGridLocation();
	virtual FIntPoint GetGridLocation_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GridLocation")
		void SetGridLocation(FIntPoint NewLoc);
	virtual void SetGridLocation_Implementation(FIntPoint NewLoc) override;

	//TODO implement interface Setter/getter for location. In this function only describe a specific way pawn is placed on a tile
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GridLocation")
		void UpdateLocation();
	virtual void UpdateLocation_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Update")
		void UpdateOnTurn();
	virtual void UpdateOnTurn_Implementation() override;

	/*
	//Some pointer is defined to any class inheriting from UObject
	UObject* pointerToAnyUObject;

	//....


	ILocatable* TheInterface = Cast<ILocatable>(pointerToAnyUObject);
	if (TheInterface)
	{
		//Don't call your functions directly, use the 'Execute_' prefix
		//the Execute_ReactToHighNoon and Execute_ReactToMidnight are generated on compile
		//you may need to compile before these functions will appear
		TheInterface->Execute_GetGridLocation (pointerToAnyUObject);

	}
	*/
};
