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

	// Disable tick until the cannon activates
	SetActorTickEnabled(false);

	// Get bounds of the area the cannon can move around
	if (!IsValid(MoveArea))
	{
		return;
	}
	MoveArea->GetActorBounds(false, Center, Bounds);
}

void AWallCannon::OnShotTimer() const
{
	auto Location = GetProjectileLocation();
	FRotator Rotation = GetActorRotation();
	auto Projectile = GetWorld()->SpawnActor<AGuidedProjectile>(ClassProjectile, Location, Rotation);
	Projectile->SetTarget(Target);
}

void AWallCannon::OnMoveTimer()
{
	// Find a random position inside the MoveArea
	FVector Offset;
	Offset.X = -Bounds.X / 2 + FMath::RandRange(0.0, Bounds.X);
	Offset.Y = -Bounds.Y / 2 + FMath::RandRange(0.0, Bounds.Y);
	Offset.Z = -Bounds.Z / 2 + FMath::RandRange(0.0, Bounds.Z);
	NextPosition = Center + Offset;
	GEngine->AddOnScreenDebugMessage(0, 10.0f, FColor::Red, NextPosition.ToString());
}

// Called every frame
void AWallCannon::Tick(float DeltaTime)
{
	GEngine->AddOnScreenDebugMessage(1, 10.0f, FColor::Blue, "Tick");
	Super::Tick(DeltaTime);

	// Don't move if we don't have a valid destination
	if (NextPosition == FVector::ZeroVector)
	{
		return;
	}

	// Consider the destination reached if we are sufficiently close
	float StepSize = DeltaTime * MoveSpeed;
	if (FVector::Dist(NextPosition, GetActorLocation()) <= StepSize)
	{
		NextPosition = FVector::ZeroVector;
		return;
	}

	// Move towards the destination
	FVector Direction = (NextPosition - GetActorLocation()).GetSafeNormal();
	AddActorWorldTransform(FTransform(FRotator(), Direction * StepSize));
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
	GetWorldTimerManager().SetTimer(TimerShot, this, &AWallCannon::OnShotTimer, ShotCooldown, true);

	// Start Moving
	SetActorTickEnabled(true);
	GetWorldTimerManager().SetTimer(TimerMove, this, &AWallCannon::OnMoveTimer, MoveCooldown, true, 0.5f);
}

void AWallCannon::DeactivateInteraction(AActor* ActivationInstigator)
{
}
