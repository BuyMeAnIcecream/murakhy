// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Runtime/Core/Public/Math/UnrealMathUtility.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.h"
#include "GridMap.generated.h"

USTRUCT()
struct FTile2DArray {
	GENERATED_BODY()
public:

	TArray<ATile*> Ar;

	ATile* operator[] (int32 i) 
	{
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
		ETileType TopTypeOfNeighbors(int TileX, int TileY);

	UPROPERTY(VisibleAnywhere, Category = Terra)
		int32 GridWidth;

	UPROPERTY(VisibleAnywhere, Category = Terra)
		int32 GridHeight;

	bool CanBeStepped(int x, int y) const;

	ATile* GetTile(int x, int y);

	ATile* GetTile(FIntPoint Location);

//	UPROPERTY(EditDefaultsOnly, Category = Spawn)
	//TODO Move to Spawner
	UFUNCTION(BlueprintCallable, Category = Spawn)
		APawn* SpawnMurakha(FIntPoint Location);

	//TODO spawnAt(tile to spawn at)
	UPROPERTY(EditDefaultsOnly, Category = Spawn)
		TSubclassOf<class APawn> PawnToSpawn;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//TODO load map / save map
};
