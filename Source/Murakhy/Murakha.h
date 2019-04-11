// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Locatable.h"

//Normal Forward Declaration
class AGridMap;

#include "Murakha.generated.h"

UENUM(BlueprintType)
enum class EDirection : uint8
{
	ET_North UMETA(DisplayName = "North"),
	ET_East UMETA(DisplayName = "East"),
	ET_South UMETA(DisplayName = "South"),
	ET_West UMETA(DisplayName = "West"),
	ET_END

};

UCLASS()
class MURAKHY_API AMurakha : public APawn, public ILocatable
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMurakha();

//	UPROPERTY(EditAnywhere, Category = "Location")
	UPROPERTY(EditAnywhere, Category = "Behavior")
		class UBehaviorTree *Behavior;
	UFUNCTION(BlueprintCallable, Category = "Search")
	TArray<APawn*> ScanForPawns();

	UPROPERTY(VisibleAnywhere, Category = "Location")
		class ATile* LocatedOn;
	
	UPROPERTY(VisibleAnywhere, Category = "Location")
	AGridMap* GridMap;
	
	UFUNCTION(BlueprintCallable, Category = "Movement")
		void Move(EDirection Direction);


	//TODO scan area
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
