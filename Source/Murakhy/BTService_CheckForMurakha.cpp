// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_CheckForMurakha.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MurakhyAIController.h"
#include "Murakha.h"
#include "Murakhy.h"

UBTService_CheckForMurakha::UBTService_CheckForMurakha()
{
	bCreateNodeInstance = true;
}
void UBTService_CheckForMurakha::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	AMurakhyAIController *MurakhaPC = Cast<AMurakhyAIController>(OwnerComp.GetAIOwner());
	/*
	if (MurakhaPC)
	{

//		AMurakha *OtherMurakha = Cast<AMurakha>(GetWorld()->get);
	}
	*/
}
