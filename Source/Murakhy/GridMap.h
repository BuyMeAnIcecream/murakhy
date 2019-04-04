// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tile.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridMap.generated.h"

USTRUCT()
struct FTile2DArray {
	GENERATED_BODY()
public:

	TArray<ATile*> Ar;

	ATile* operator[] (int32 i) {
		return Ar[i];
	}

	void Add(ATile* tile) {
		Ar.Add(tile);
	}
};


UCLASS()
class MURAKHY_API AGridMap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridMap();

	TArray<FTile2DArray> Tiles;

	UFUNCTION(BlueprintCallable, Category = Terra)
		ETileType TopTypeOfNeighbors(int tileX, int tileY);
	UPROPERTY(VisibleAnywhere, Category = Terra)
		int32 GridWidth;
	UPROPERTY(VisibleAnywhere, Category = Terra)
		int32 GridHeight;

	bool IsTileStepable(int x, int y);

	ATile* GetTile(int x, int y);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//TODO load map / save map
};
