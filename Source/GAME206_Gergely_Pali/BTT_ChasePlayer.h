// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BTT_ChasePlayer.generated.h"

/**
 * 
 */
UCLASS()
class GAME206_GERGELY_PALI_API UBTT_ChasePlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
	float ChaseSpeed = 500.0f;

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
