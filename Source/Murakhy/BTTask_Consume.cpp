// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_Consume.h"
#include "Murakha.h"
#include "MurakhyAIController.h"
#include "EBioParameter.h"
#include "Tile.h"

EBTNodeResult::Type UBTTask_Consume::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMurakhyAIController* PC = Cast<AMurakhyAIController>(OwnerComp.GetAIOwner());
	if (PC)
	{
		const EDirection ChosenDir = EDirection(OwnerComp.GetBlackboardComponent()->GetValueAsEnum(OwnerComp.GetBlackboardComponent()->GetKeyName(PC->MovingDirectionID)));
		const EBioParameter Prioritized = EBioParameter(OwnerComp.GetBlackboardComponent()->GetValueAsEnum(OwnerComp.GetBlackboardComponent()->GetKeyName(PC->BioPriorityID)));
		AMurakha* MyPawn = Cast<AMurakha>(PC->GetPawn());
		if (MyPawn)
		{
			MyPawn->Consume(Prioritized, MyPawn->LocatedOn);
			return EBTNodeResult::Succeeded;
			
		}
	}
	return EBTNodeResult::Failed;
}
