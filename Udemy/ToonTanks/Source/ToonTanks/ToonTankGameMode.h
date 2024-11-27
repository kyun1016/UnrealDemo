// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTankGameMode.generated.h"

class ATank;
class AToonTankPlayerController;
/**
 *
 */
UCLASS()
class TOONTANKS_API AToonTankGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(TObjectPtr<AActor> DeadActor);

protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintImplementableEvent)
		void StartGame();

private:
	void HandleGameStart();

private:
	TObjectPtr<ATank> Tank;
	TObjectPtr<AToonTankPlayerController> ToonTankPlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Timer", meta = (AllowPrivateAccess = "true"))
		float StartDelay = 3.f;
};
