// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

void AEnemyController::OnPossess(APawn* const CharacterPawn)
{
	Super::OnPossess(CharacterPawn);
	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
		// create a local pointer to the BlackBoardComponent, we need that to
		// manipulate the variables inside it
		UseBlackboard(BehaviorTree->BlackboardAsset, BlackBoardComp);
	}
}

AEnemyController::AEnemyController(FObjectInitializer const& ObjectInitializer)
{
	// create a new AI Sight perception component and fill with default values
	SenseComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Sight Perception Component"));
	SetPerceptionComponent(*SenseComp);
	UAISenseConfig_Sight* SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SightConfig->SightRadius = 1000.0f;
	SightConfig->LoseSightRadius = SightConfig->SightRadius + 100.0f;
	SightConfig->PeripheralVisionAngleDegrees = 90.0f;
	SightConfig->SetMaxAge(1.0f);
	SightConfig->AutoSuccessRangeFromLastSeenLocation = 0.0f;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
	// if anything is notified by the perceptor, this method will be called
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyController::OnTargetActorUpdated);
}

void AEnemyController::OnTargetActorUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	// if player seen, start to chase
	if (Actor->ActorHasTag("Player") && Stimulus.IsActive())
	{
		BlackBoardComp->SetValueAsBool("ChasePlayer", true);
		BlackBoardComp->SetValueAsObject("EnemyActor", Actor);
		BlackBoardComp->ClearValue("EnemyLoc");
	}
	// if player is moving out of line of sight, move to the last known location
	if (Actor->ActorHasTag("Player") && !Stimulus.IsActive())
	{
		BlackBoardComp->SetValueAsVector("EnemyLoc", Actor->GetActorLocation());
		BlackBoardComp->ClearValue("EnemyActor");
	}
}