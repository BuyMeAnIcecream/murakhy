// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_SearchForPrioritized.h"
#include "MurakhyAIController.h"
#include "Murakha.h"
#include "GridMap.h"

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
			//get array of neighbors
			ILocatable * OwnerLocatable = CastChecked<ILocatable>(OwnerPawn);
			FIntPoint OwnerLoc = OwnerLocatable->Execute_GetGridLocation(OwnerPawn);
			TArray<ATile*> Neighbors;
			OwnerPawn->GridMap->GetNeighborsOf(Neighbors,OwnerLoc,PC->VisionRadius);

			ETileType SearchedType =  ETileType(OwnerComp.GetBlackboardComponent()->GetValueAsEnum(OwnerComp.GetBlackboardComponent()->GetKeyName(PC->BioPriorityID)));
			int HighestVal = 0;
			ATile *Richest = nullptr;
			for(auto& Neighbor: Neighbors)
			{
				if(Neighbor->ConsumableCurrent > HighestVal)
				{
					Richest = Neighbor;
					HighestVal = Richest->ConsumableCurrent;
				}
			}
			//NOT SURE IF THIS SHOULD BE SPLIT INTO EXTRA BTSERVICE
			EDirection DesiredDirection = AGridMap::CoordinatesToDirection(Richest->LocationOnMap - OwnerPawn->LocatedOn->LocationOnMap);
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Enum>(PC->MovingDirectionID, static_cast<UBlackboardKeyType_Enum::FDataType>(DesiredDirection));
			//			AGridMap::CoordinatesToDirection()
			//			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Bool>(PC->TurnCompleteID, true);
		
		}
	}
}


