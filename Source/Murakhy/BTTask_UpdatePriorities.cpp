// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_UpdatePriorities.h"
#include "MurakhyAIController.h"
#include "Murakha.h"


EBTNodeResult::Type UBTTask_UpdatePriorities::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMurakhyAIController* PC = Cast<AMurakhyAIController>(OwnerComp.GetAIOwner());

	if (PC)
	{
		AMurakha * OwnerPawn = Cast<AMurakha>(PC->GetPawn());
		if (OwnerPawn)
		{
			//TODO add priority curves. I love them and want them
			//For now lets prioritize the lowest value
			uint32 Lowest = 255;
			EBioParameter BioPriority = EBioParameter::EBP_END;
			for (auto& Elem : OwnerPawn->CurrentBioParam)
			{
				if (Elem.Value < Lowest)
				{
					Lowest = Elem.Value;
					BioPriority = Elem.Key;
				}
			}
			if (BioPriority == EBioParameter::EBP_END)
			{
				UE_LOG(LogTemp, Warning, TEXT("wrong bio priority"));
			}
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Enum>(PC->BioPriorityID, static_cast<UBlackboardKeyType_Enum::FDataType>(BioPriority));
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
