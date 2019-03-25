// Fill out your copyright notice in the Description page of Project Settings.

#include "MurakhyAIController.h"
#include "Murakha.h"
AMurakhyAIController::AMurakhyAIController()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree"));
}

void AMurakhyAIController::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);

	AMurakha *Murakha = Cast<AMurakha>(InPawn);

	if (Murakha &&	Murakha->Behavior)
	{
		BlackboardComp->InitializeBlackboard(*Murakha->Behavior->BlackboardAsset);

		MurakhaKeyID = BlackboardComp->GetKeyID("Target");
		BehaviorTreeComp->StartTree(*Murakha->Behavior);

		
	}
}

