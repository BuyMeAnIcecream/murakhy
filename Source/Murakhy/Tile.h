// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Materials/Material.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Tile.generated.h"


UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class ETileType : uint8
{
	ET_Water UMETA(DisplayName = "Water"),
	ET_Desert UMETA(DisplayName = "Desert"),
	ET_Evil	UMETA(DisplayName = "Glow"),
	ET_Snow UMETA(DisplayName = "Snow"),
	ET_END
};


UCLASS()
class MURAKHY_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
//	UPROPERTY(EditDefaultsOnly)
//		UMaterialInterface* Material;
	UFUNCTION(BlueprintCallable, Category = Tile)
		void UpdateMaterial();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
		ETileType TileType;

	UPROPERTY(EditDefaultsOnly, Category = Tile)
	TMap<ETileType, UMaterial*> MaterialMap;

	UPROPERTY(EditDefaultsOnly, Category = Tile)
		UStaticMeshComponent* Mesh;

	UPROPERTY(BlueprintReadOnly, Category = Tile)
		USceneComponent* Root;


//	UPROPERTY(EditAnywhere, Category = Tile)
//		Material

};
