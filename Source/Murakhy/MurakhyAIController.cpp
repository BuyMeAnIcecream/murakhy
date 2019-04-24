// Fill out your copyright notice in the Description page of Project Settings.

#include "MurakhyAIController.h"
#include "Murakha.h"

void AMurakhyAIController::BeginPlay()
{
	Super::BeginPlay();
	//IsTurnComplete = false;
}

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

		BioPriorityID = BlackboardComp->GetKeyID("BioPriority");
		TurnCompleteID = BlackboardComp->GetKeyID("TurnComplete");
		BehaviorTreeComp->StartTree(*Murakha->Behavior);
	}
}

void AMurakhyAIController::UpdateOnTurn_Implementation()
{
	BlackboardComp->SetValueAsBool("TurnComplete", false);
}

