// Fill out your copyright notice in the Description page of Project Settings.


#include "WallCannon.h"

// Sets default values
AWallCannon::AWallCannon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWallCannon::BeginPlay()
{
	Super::BeginPlay();
}

void AWallCannon::OnShotTimer() const
{
	auto Location = GetProjectileLocation();
	FRotator Rotation = GetActorRotation();
	auto Projectile = GetWorld()->SpawnActor<AGuidedProjectile>(ClassProjectile, Location, Rotation);
	Projectile->SetTarget(Target);
}

// Called every frame
void AWallCannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWallCannon::ToggleInteraction(AActor* ActivationInstigator)
{
}

void AWallCannon::ActivateInteraction(AActor* ActivationInstigator)
{
	// Ensure that activation triggers only once
	if (bHasBeenActivated)
	{
		return;
	}
	bHasBeenActivated = true;

	// Set target for projectiles
	Target = ActivationInstigator;

	// Start shooting
	GetWorldTimerManager().SetTimer(TimerShot, this, &AWallCannon::OnShotTimer, Cooldown, true);
}

void AWallCannon::DeactivateInteraction(AActor* ActivationInstigator)
{
}
