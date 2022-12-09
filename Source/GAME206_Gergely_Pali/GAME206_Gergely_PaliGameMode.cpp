// Copyright Epic Games, Inc. All Rights Reserved.

#include "GAME206_Gergely_PaliGameMode.h"
#include "GAME206_Gergely_PaliCharacter.h"
#include "CountdownSceneComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Target.h"

AGAME206_Gergely_PaliGameMode::AGAME206_Gergely_PaliGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}

void AGAME206_Gergely_PaliGameMode::HandleTargetDied()
{
	++CurrentScore;
	if (CurrentScore >= MaxScore)
	{
		GameWon.Broadcast();
	}
	// if the target dies(meaning it got hit) the game mode will add 5 seconds to the game timer as a bonus and spawns a new target to shoot
	GameTimer += TimerIncrease;
	SpawnNewTarget();
}

// spawn a new target on a random location
void AGAME206_Gergely_PaliGameMode::SpawnNewTarget()
{
	SpawnLocation = GenerateNewSpawnLocation();
	ATarget* NewTarget = (ATarget*)GetWorld()->SpawnActor(ATarget::StaticClass(), SpawnLocation);
}

FTransform* AGAME206_Gergely_PaliGameMode::GenerateNewSpawnLocation()
{
	int x = FMath::RandRange(200, 2800);
	int y = FMath::RandRange(200, 3300);

	FTransform* newLocation = new FTransform(FVector3d(x, y, 1000));
	return newLocation;
}

void AGAME206_Gergely_PaliGameMode::ExitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}

void AGAME206_Gergely_PaliGameMode::PauseAndDisplayResult()
{
	// disable the input for the controller so the player can see the final result of the game
	UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->DisableInput(GetWorld()->GetFirstPlayerController());

	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &AGAME206_Gergely_PaliGameMode::ExitGame, 3.0f, false);
}