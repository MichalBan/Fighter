// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GuidedProjectile.generated.h"

UCLASS()
class FIGHTER_API AGuidedProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGuidedProjectile();

	// Set target to follow
	void SetTarget(AActor* InTarget);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called after collision with anything
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
	// Called after the projectile expires
	void OnExpireTimer();

	// Explode dealing damage in radius
	void Explode();

	// Target to follow
	UPROPERTY()
	AActor* Target;

	// Timer for expiration
	FTimerHandle TimerExpire;

	// Time after which the projectile gets destroyed
	UPROPERTY(EditAnywhere, Category = "Projectile", meta = (ClampMin = 5, ClampMax = 50, Units = "s"))
	float TimeToLive = 10.0f;
	// Speed at which the projectile flies 
	UPROPERTY(EditAnywhere, Category = "Projectile", meta = (ClampMin = 100, ClampMax = 10000, Units = "cm/s"))
	float Velocity = 1000.0f;
	// Speed at which the projectile rotates
	UPROPERTY(EditAnywhere, Category = "Projectile", meta = (ClampMin = 30, ClampMax = 360, Units = "deg/s"))
	float RotationSpeed = 100.0f;

	// Explosion Radius 
	UPROPERTY(EditAnywhere, Category = "Explosion", meta = (ClampMin = 100, ClampMax = 1000, Units = "cm"))
	float ExplosionRadius = 300.0f;

	// Explosion Damage 
	UPROPERTY(EditAnywhere, Category = "Explosion", meta = (ClampMin = 0, ClampMax = 100, Units = "cm"))
	float ExplosionDamage = 1.0f;

	// Explosion Knockback 
	UPROPERTY(EditAnywhere, Category = "Explosion", meta = (ClampMin = 1000, ClampMax = 5000, Units = "cm/s"))
	float ExplosionImpulse = 1000.0f;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
