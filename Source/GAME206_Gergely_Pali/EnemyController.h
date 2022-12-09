// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class GAME206_GERGELY_PALI_API AEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	void OnPossess(APawn* const CharacterPawn) override;
	AEnemyController(FObjectInitializer const& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBehaviorTree* BehaviorTree;

	UPROPERTY()
	class UBlackboardComponent* BlackBoardComp;
	
private:
	UAIPerceptionComponent* SenseComp;

	UFUNCTION()
	void OnTargetActorUpdated(AActor* Actor, FAIStimulus Stimulus);

};
