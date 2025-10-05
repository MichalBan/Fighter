// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "SprintSphere.generated.h"

UCLASS()
class FIGHTER_API ASprintSphere : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASprintSphere();
	virtual void SetOwner(AActor* NewOwner) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp,
	                       bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse,
	                       const FHitResult& Hit) override;

	/** Amount of damage a collision with the sphere will deal */
	UPROPERTY(EditAnywhere, Category="Combat", meta = (ClampMin = 0, ClampMax = 100))
	int CollisionDamage = 1.0f;
	/** Amount of knockback impulse a collision with the sphere will apply */
	UPROPERTY(EditAnywhere, Category="Combat", meta = (ClampMin = 0, ClampMax = 10000, Units = "cm/s"))
	float CollisionImpulse = 1500.0f;
	/** Amount of upwards impulse a melee attack will apply */
	UPROPERTY(EditAnywhere, Category = "Melee Attack|Damage", meta = (ClampMin = 0, ClampMax = 1000, Units = "cm/s"))
	float LaunchImpulse = 500.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USphereComponent* Collider;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
