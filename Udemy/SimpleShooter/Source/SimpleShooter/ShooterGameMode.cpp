// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacter.h"

void AShooterGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void AShooterGameMode::HandleGameStart()
{
	// TODO: 게임 승리 조건 추가
	// Player = Cast<AShooterCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
}
