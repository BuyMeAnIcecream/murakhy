// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_Move.h"
#include "MurakhyAIController.h"
#include "EDirection.h"
#include "Murakha.h"


EBTNodeResult::Type UBTTask_Move::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMurakhyAIController* PC = Cast<AMurakhyAIController>(OwnerComp.GetAIOwner());
	if (PC)
	{
		const EDirection ChosenDir = EDirection(OwnerComp.GetBlackboardComponent()->GetValueAsEnum(OwnerComp.GetBlackboardComponent()->GetKeyName(PC->MovingDirectionID)));
		AMurakha* MyPawn = Cast<AMurakha>(PC->GetPawn());
		if(MyPawn)
		{
			if(MyPawn->Move(ChosenDir))
			{
				UE_LOG(LogTemp, Warning, TEXT("Move Succeeded"));
				return EBTNodeResult::Succeeded;
			}
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Move Failed"));
	return EBTNodeResult::Failed;
}
