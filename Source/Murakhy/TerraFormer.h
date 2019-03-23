// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Tile.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "CoreMinimal.h"
//#include "GameFramework/Actor.h"
#include "TerraFormer.generated.h"


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
class MURAKHY_API ATerraFormer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATerraFormer();

	UPROPERTY(EditAnywhere, Category = Terra)
	int32 Width;
	UPROPERTY(EditAnywhere, Category = Terra)
	int32 Height;
	UPROPERTY(EditAnywhere, Category = Terra)
	TMap<ETileType, float> LikelihoodMap;

	UPROPERTY(EditDefaultsOnly, Category = Terra)
	TSubclassOf<class ATile> Tile;
	//	UPROPERTY(VisibleAnywhere, Category = Terra)
		TArray<FTile2DArray> Tiles;
	
	UFUNCTION(BlueprintCallable, Category = Terra)
	ETileType TopTypeOfNeighbors(int tileX, int tileY);

	UFUNCTION(BlueprintCallable, Category = Terra)
		void TerraForm();

	UFUNCTION(BlueprintCallable, Category = Terra)
	ETileType RandomizeFromMap();

	UFUNCTION(BlueprintCallable, Category = Terra)
		void Smooth();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
//	TArray<TArray<ATile*>> Terra;

};
