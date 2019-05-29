// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_IsReadyToReproduce.h"
#include "Murakha.h"
#include "MurakhyAIController.h"

EBTNodeResult::Type UBTTask_IsReadyToReproduce::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AMurakhyAIController* PC = Cast<AMurakhyAIController>(OwnerComp.GetAIOwner());

	if (PC)
	{
		AMurakha * OwnerPawn = Cast<AMurakha>(PC->GetPawn());
		if (OwnerPawn)
		{
			uint32 Lowest = 255;
			EBioParameter BioPriority = EBioParameter::EBP_END;
			for (auto& Elem : OwnerPawn->CurrentBioParam)
			{
				if (OwnerPawn->BioParams[Elem.Key].Sufficient >= Elem.Value)
				{
					UE_LOG(LogTemp, Warning, TEXT("not ready yet"));
					return EBTNodeResult::Failed;
				}
				UE_LOG(LogTemp, Warning, TEXT("ready"));
				return EBTNodeResult::Succeeded;
			}
			if (BioPriority == EBioParameter::EBP_END)
			{
				UE_LOG(LogTemp, Warning, TEXT("wrong bio priority"));
			}			
		}
	}
	return EBTNodeResult::Failed;
}
