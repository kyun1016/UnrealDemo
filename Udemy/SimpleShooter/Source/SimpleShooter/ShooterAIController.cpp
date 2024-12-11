// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();


	if (AIBehavior)
	{
		RunBehaviorTree(AIBehavior);
		TObjectPtr<AActor> target = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		Blackboard->SetValueAsVector(TEXT("PlayerLocation"), target->GetActorLocation());
		Blackboard->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}

	//TObjectPtr<AActor> target = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	//SetFocus(target);
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//
	//MoveToActor(target, 200.f);
}
