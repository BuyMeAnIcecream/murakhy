// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_UpdatePriorities.h"
#include "MurakhyAIController.h"
#include "Murakha.h"

UBTService_UpdatePriorities::UBTService_UpdatePriorities()
{
//	Super::
	NodeName = "Update Priorities";

//	bNotifyBecomeRelevant = true;    // necessarily!!!
	bCreateNodeInstance = true;
}

void UBTService_UpdatePriorities::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	
	AMurakhyAIController* PC = Cast<AMurakhyAIController>(OwnerComp.GetAIOwner());
	
	if(PC)
	{
		AMurakha * OwnerPawn = Cast<AMurakha>(PC->GetPawn());
		if(OwnerPawn)
		{
			//TODO remove this by calling the whole thing on value changed
//			if(OwnerComp.GetBlackboardComponent()->GetValueAsBool("TurnComplete"))
//			{
//				return;
//			}
			//TODO add priority curves. I love them and want them
			//For now lets prioritize the lowest value
			uint32 Lowest = 255;
			EBioParameter BioPriority = EBioParameter::EBP_END;
			for (auto& Elem : OwnerPawn->BioParams)
			{
				if (Elem.Value.Current < Lowest)
				{
					Lowest = Elem.Value.Current;
					BioPriority = Elem.Key;
				}
			}
			if(BioPriority == EBioParameter::EBP_END)
			{
				UE_LOG(LogTemp, Warning, TEXT("wrong bio priority"));
			}
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Enum>(PC->BioPriorityID, static_cast<UBlackboardKeyType_Enum::FDataType>(BioPriority));
//			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Bool>(PC->TurnCompleteID, true);
		}
	}

}
