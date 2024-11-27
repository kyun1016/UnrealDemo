// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTankPlayerController.h"

void AToonTankGameMode::ActorDied(TObjectPtr<AActor> DeadActor)
{
	if (TObjectPtr<ABasePawn> Pawn = Cast<ABasePawn>(DeadActor))
	{
		Pawn->HandleDestruction();
		// Exception: Tank & Player Case
		if (DeadActor == Tank && ToonTankPlayerController)
		{
			ToonTankPlayerController->SetPlayerEnabledState(false);
		}
	}
}

void AToonTankGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void AToonTankGameMode::HandleGameStart()
{
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTankPlayerController = Cast<AToonTankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	if (ToonTankPlayerController)
	{
		ToonTankPlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate InputDelegate = FTimerDelegate::CreateUObject(
			ToonTankPlayerController,
			&AToonTankPlayerController::SetPlayerEnabledState,
			true
		);
		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, InputDelegate, StartDelay, false);
	}
		
}