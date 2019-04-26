// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Updatable.h"
#include "MurakhyAIController.generated.h"

/**
 * 
 */
UCLASS()
class MURAKHY_API AMurakhyAIController : public AAIController, public IUpdatable
{
	GENERATED_BODY()

	UPROPERTY(transient)
	class UBlackboardComponent* BlackboardComp;

	UPROPERTY(transient)
	class UBehaviorTreeComponent* BehaviorTreeComp;

	virtual void BeginPlay() override;
public:
	AMurakhyAIController();

	virtual void Possess(APawn* InPawn) override;

	FBlackboard::FKey BioPriorityID;
	FBlackboard::FKey TurnCompleteID;
	FBlackboard::FKey MovingDirectionID;
	//const bool& GetIsTurnComplete() const { return IsTurnComplete; }
	//void SetIsTurnComplete(const bool& itc) { IsTurnComplete = itc; }

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Update")
		void UpdateOnTurn();
	virtual void UpdateOnTurn_Implementation() override;

	UPROPERTY(EditDefaultsOnly, Category = "Behaviour")
		uint8 VisionRadius;
};
