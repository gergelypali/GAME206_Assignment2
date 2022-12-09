// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GAME206_Gergely_PaliGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameWon);

UCLASS(minimalapi)
class AGAME206_Gergely_PaliGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGAME206_Gergely_PaliGameMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int GameTimer = 15;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TimerIncrease = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxScore = 10;

	void HandleTargetDied();

	void SpawnNewTarget();

	void ExitGame();

	void PauseAndDisplayResult();

	FGameWon GameWon;

private:
	int CurrentScore = 0;

	FTransform* SpawnLocation;

	FTransform* GenerateNewSpawnLocation();
};



