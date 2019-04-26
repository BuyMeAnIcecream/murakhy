// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Materials/Material.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Locatable.h"
#include "Updatable.h"
class AMurakha;
#include "EBioParameter.h"
#include "Tile.generated.h"


UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class ETileType : uint8
{
	ET_Water UMETA(DisplayName = "Water"),
	ET_Desert UMETA(DisplayName = "Desert"),
	ET_Evil	UMETA(DisplayName = "Glow"),
	ET_Snow UMETA(DisplayName = "Snow"),
	ET_End
};

USTRUCT(BlueprintType)
struct FConsumableData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Data)
	EBioParameter TypeProduced;

	UPROPERTY(EditDefaultsOnly, Category = Data)
	uint8 ConsumableMax;

	UPROPERTY(EditDefaultsOnly, Category = Data)
	uint8 AmountProducedPerTurn;

	UPROPERTY(EditDefaultsOnly, Category = Data)
	uint8 RandomExtraProducedPerTurn;
};

UCLASS()
class MURAKHY_API ATile : public AActor, public IUpdatable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
/*
	UPROPERTY(VisibleAnywhere, Category = Tile)
		TArray<TScriptInterface<ILocatable*>> StoredLocatables;
		*/

public:
	UFUNCTION(BlueprintCallable, Category = Tile)
	void UpdateMaterial();

	UPROPERTY(VisibleAnywhere, Category = Tile)
	bool IsBusy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
	ETileType TileType;

	UPROPERTY(EditDefaultsOnly, Category = Tile)
	TMap<ETileType, UMaterial*> MaterialMap;

	UPROPERTY(EditDefaultsOnly, Category = Tile)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = Tile)
	AMurakha *MurakhaOnTile;

	UPROPERTY(BlueprintReadOnly, Category = Tile)
	USceneComponent* Root;
	
	UPROPERTY(EditDefaultsOnly, Category = "ConsumableData")
	TMap<ETileType, FConsumableData> ConsumableInfo;

	UPROPERTY(VisibleAnywhere, Category = Consumable)
	uint8 ConsumableCurrent;

	UPROPERTY(VisibleInstanceOnly, Category = Tile)
	FIntPoint LocationOnMap;
/*
	void AddLocatable(TScriptInterface<ILocatable> *Locatable);

	void RemoveLocatable(TScriptInterface<ILocatable> *Locatable);
*/

	UFUNCTION(BlueprintCallable, Category = Consumable)
	void ProduceConsumable();

	void MovedOff();
	
	void MovedOn(AMurakha* Murakha);

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Update")
	void UpdateOnTurn();
	virtual void UpdateOnTurn_Implementation() override;

};