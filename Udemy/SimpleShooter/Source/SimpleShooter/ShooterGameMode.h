// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShooterGameMode.generated.h"

class AShooterCharacter;
/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
private:
	void HandleGameStart();

private:
	// TObjectPtr<AShooterCharacter> Player;
};
