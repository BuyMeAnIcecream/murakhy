// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MurakhyAIController.generated.h"

/**
 * 
 */
UCLASS()
class MURAKHY_API AMurakhyAIController : public AAIController
{
	GENERATED_BODY()

		UPROPERTY(transient)
		class UBlackboardComponent* BlackboardComp;

	UPROPERTY(transient)
		class UBehaviorTreeComponent* BehaviorTreeComp;
public:
	AMurakhyAIController();

	virtual void Possess(APawn* InPawn) override;
	uint8 MurakhaKeyID;
};
