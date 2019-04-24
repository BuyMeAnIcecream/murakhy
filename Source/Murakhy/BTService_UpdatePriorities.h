// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_UpdatePriorities.generated.h"


/**
 * 
 */
UCLASS()
class MURAKHY_API UBTService_UpdatePriorities : public UBTService
{
	GENERATED_BODY()

public:

	UBTService_UpdatePriorities();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
