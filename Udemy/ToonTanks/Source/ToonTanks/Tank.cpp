// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ATank::ATank()
	: Speed(500.0f)
	, TurnRate(180.0f)
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerControllerRef)
	{
		FHitResult HitResult;
		if (PlayerControllerRef->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult))
		{
			DrawDebugSphere(
				GetWorld(),
				HitResult.ImpactPoint,
				30.f,
				12,
				FColor::Red,
				false,
				-1.f
			);

			RotateTurret(HitResult.ImpactPoint);
		}
	}
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerRef = Cast<APlayerController>(GetController());
	DrawDebugSphere(
		GetWorld(),
		GetActorLocation() + FVector(0.f, 0.f, 200.f),
		100.f,
		12,
		FColor::Red,
		true,
		30.f
	);
}

void ATank::Move(float Value)
{
	// UE_LOG(LogTemp, Display, TEXT("Value: %f"), Value);
	// FVector DeltaLocation = FVector::ZeroVector;
	// DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
	FVector DeltaLocation{ Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this), 0.f, 0.f };
	AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value)
{
	// FRotator DeltaRotation = FRotator::ZeroRotator;
	// DeltaRotation.Yaw = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
	FRotator DeltaRotation{ 0.f, Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this), 0.f };
	AddActorLocalRotation(DeltaRotation, true);
}
