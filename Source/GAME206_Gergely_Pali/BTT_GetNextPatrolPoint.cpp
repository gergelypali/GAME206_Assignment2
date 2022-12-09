// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_GetNextPatrolPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "EnemyController.h"

EBTNodeResult::Type UBTT_GetNextPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AEnemyController* const Cont = Cast<AEnemyController>(OwnerComp.GetAIOwner()))
	{
		if (ATP_ThirdPersonCharacter* const Char = Cast<ATP_ThirdPersonCharacter>(Cont->GetCharacter()))
		{
			if (Char->PatrolPathOnBegin.Num() > 0)
			{
				int index = OwnerComp.GetBlackboardComponent()->GetValueAsInt("PatrolIndex");

				OwnerComp.GetBlackboardComponent()->SetValueAsVector("PatrolLocation", Char->PatrolPathOnBegin[index]);

				// circular loop over the patrolpath array, so AI will loop around forever
				if (Char->PatrolPathOnBegin.Num() - 1 == index)
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsInt("PatrolIndex", 0);
				}
				else
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsInt("PatrolIndex", index + 1);
				}
				return EBTNodeResult::Succeeded;
			}
			return EBTNodeResult::Failed;
		}
		return EBTNodeResult::Failed;
	}
	return EBTNodeResult::Failed;
}