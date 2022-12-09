// Fill out your copyright notice in the Description page of Project Settings.


#include "StopTheChase.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UStopTheChase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // set to false so the chase loop can end at some point
	OwnerComp.GetBlackboardComponent()->SetValueAsBool("ChasePlayer", false);
	return EBTNodeResult::Succeeded;
}
