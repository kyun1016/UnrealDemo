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
	// TODO: ���� �¸� ���� �߰�
	// Player = Cast<AShooterCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
}
