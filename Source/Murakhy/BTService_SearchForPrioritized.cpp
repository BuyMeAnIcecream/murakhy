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
			
			const EBioParameter SearchedType =  EBioParameter(OwnerComp.GetBlackboardComponent()->GetValueAsEnum(OwnerComp.GetBlackboardComponent()->GetKeyName(PC->BioPriorityID)));
			
			//look around for consumable
			TArray<ATile*> Neighbors;
			OwnerPawn->GridMap->GetNeighborsOf(Neighbors, OwnerLoc, PC->VisionRadius);
			int HighestVal = 0;
			ATile *Richest = nullptr;
			for(auto& Neighbor: Neighbors)
			{
				if(Neighbor->ConsumableStored[SearchedType] > HighestVal)
				{
					Richest = Neighbor;
					HighestVal = Richest->ConsumableStored[SearchedType];
				}
			}

			//see if current has more than richest. ahem, this means, Murakha doesn't consume resource that is under it's feet but looks for a better piece first
			//Check if current tile contains more prioritized than neighbors and make move/stay choice based on that
			
			
			//STAY AND EAT
			if(HighestVal > 0 && OwnerPawn->LocatedOn->ConsumableStored[SearchedType] >= HighestVal)
			{
				UE_LOG(LogTemp, Warning, TEXT("STAY AND EAT"));
				OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Bool>(PC->ShouldConsumeID, static_cast<UBlackboardKeyType_Bool::FDataType>(true));
			}
			//WANDER
			else if(HighestVal == 0)
			{
				UE_LOG(LogTemp, Warning, TEXT("Wandering"));
				EDirection DesiredDirection;
				//random direction
				//TODO TEST.
				do
				{
					DesiredDirection = EDirection(FMath::RandRange(0, int(EDirection::ET_NorthWest)));
				} while (!OwnerPawn->GridMap->IsMoveAllowed(OwnerPawn,DesiredDirection));
	
				OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Enum>(PC->MovingDirectionID, static_cast<UBlackboardKeyType_Enum::FDataType>(DesiredDirection));
				OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Bool>(PC->ShouldConsumeID, static_cast<UBlackboardKeyType_Bool::FDataType>(false));
			}
			//MOVE TO NEAREST RICHEST
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Moving to nearest reachest"));
				EDirection DesiredDirection = AGridMap::CoordinatesToDirection(Richest->LocationOnMap - OwnerPawn->LocatedOn->LocationOnMap);
				OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Enum>(PC->MovingDirectionID, static_cast<UBlackboardKeyType_Enum::FDataType>(DesiredDirection));
				OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Bool>(PC->ShouldConsumeID, static_cast<UBlackboardKeyType_Bool::FDataType>(false));
			}
			
		}
	}
}