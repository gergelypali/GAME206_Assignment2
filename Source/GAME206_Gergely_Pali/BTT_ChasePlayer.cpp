// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_ChasePlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "EnemyController.h"
#include "GameFramework/CharacterMovementComponent.h"


EBTNodeResult::Type UBTT_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AEnemyController* const Cont = Cast<AEnemyController>(OwnerComp.GetAIOwner()))
	{
		if (ATP_ThirdPersonCharacter* const Char = Cast<ATP_ThirdPersonCharacter>(Cont->GetCharacter()))
		{
			Char->GetCharacterMovement()->MaxWalkSpeed = ChaseSpeed;
			return EBTNodeResult::Succeeded;
		}
		return EBTNodeResult::Failed;
	}
	return EBTNodeResult::Failed;
}