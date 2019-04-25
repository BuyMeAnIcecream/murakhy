// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_SearchForPrioritized.h"
#include "MurakhyAIController.h"
#include "Murakha.h"

UBTService_SearchForPrioritized::UBTService_SearchForPrioritized()
{
	NodeName = "Search For Prioritized";
	bCreateNodeInstance = true;
}

void UBTService_SearchForPrioritized::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	AMurakhyAIController* PC = Cast<AMurakhyAIController>(OwnerComp.GetAIOwner());

	if (PC)
	{
		AMurakha * OwnerPawn = Cast<AMurakha>(PC->GetPawn());
		if (OwnerPawn)
		{
			ILocatable * OwnerLocatable = CastChecked<ILocatable>(OwnerPawn);
			FIntPoint OwnerLoc = OwnerLocatable->Execute_GetGridLocation(OwnerPawn);

//			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Enum>(PC->BioPriorityID, static_cast<UBlackboardKeyType_Enum::FDataType>(BioPriority));
			//			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Bool>(PC->TurnCompleteID, true);
		}
	}
}


