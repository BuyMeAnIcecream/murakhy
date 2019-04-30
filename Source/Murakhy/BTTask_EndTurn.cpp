// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_EndTurn.h"
#include "MurakhyAIController.h"

/*
UBTTask_EndTurn::UBTTask_EndTurn(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "SetValue";
	TaskResult = EBTNodeResult::Succeeded;
}
*/

EBTNodeResult::Type UBTTask_EndTurn::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMurakhyAIController* PC = Cast<AMurakhyAIController>(OwnerComp.GetAIOwner());
	if(PC)
	{
		OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Bool>(PC->TurnCompleteID, true);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
