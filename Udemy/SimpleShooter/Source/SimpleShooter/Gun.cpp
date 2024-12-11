// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DamageEvents.h"

// Sets default values
AGun::AGun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}

void AGun::PullTrigger()
{
	// UE_LOG(LogTemp, Warning, TEXT("You've been shot!"));
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));


	// Case 1. Pawn
	TObjectPtr<APawn> OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn)
	{
		TObjectPtr<AController> OwnerController = OwnerPawn->GetController();
		if (OwnerController)
		{
			FVector Location;
			FRotator Rotation;
			OwnerController->GetPlayerViewPoint(Location, Rotation);
			// DrawDebugCamera(GetWorld(), Location, Rotation, 90, 2, FColor::Red, true);

			FVector End = Location + Rotation.Vector() * MaxRange;
			FHitResult Hit;
			if (GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1))
			{
				// DrawDebugLine(GetWorld(), Location, Hit.Location, FColor::Blue, true);
				// DrawDebugPoint(GetWorld(), Hit.Location, 20, FColor::Red, true);
				FVector ShotDirection{ -Rotation.Vector() };
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactFlash, Hit.Location, ShotDirection.Rotation());
				
				if (Hit.GetActor())
				{
					UE_LOG(LogTemp, Warning, TEXT("You've been shot!"));
					FPointDamageEvent DamageEvent{ Damage, Hit, ShotDirection, nullptr };
					Hit.GetActor()->TakeDamage(Damage, DamageEvent, OwnerController, this);
				}
			}
		}
	}
	
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

