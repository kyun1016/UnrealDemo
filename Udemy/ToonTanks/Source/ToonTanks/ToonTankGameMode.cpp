// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTankPlayerController.h"

void AToonTankGameMode::ActorDied(TObjectPtr<AActor> DeadActor)
{
	if (TObjectPtr<ABasePawn> Pawn = Cast<ABasePawn>(DeadActor))
		Pawn->HandleDestruction();

	// Handling Gameover
	if (DeadActor == Tank)
	{
		if (ToonTankPlayerController)
			ToonTankPlayerController->SetPlayerEnabledState(false);
		GameOver(false);
	}
	else if (TObjectPtr<ATower> Tower = Cast<ATower>(DeadActor))
	{
		if (--TargetTowers == 0)
			GameOver(true);
	}
}

void AToonTankGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void AToonTankGameMode::HandleGameStart()
{
	TargetTowers = GetTargetTowerCount();
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

int32 AToonTankGameMode::GetTargetTowerCount()
{
	//TArray<TObjectPtr<AActor>> Towers;
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
	return Towers.Num();
}
