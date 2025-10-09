// Fill out your copyright notice in the Description page of Project Settings.


#include "GuidedProjectile.h"

#include "CombatDamageable.h"
#include "Engine/OverlapResult.h"

// Sets default values
AGuidedProjectile::AGuidedProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Disable collision to prevent coliding with the shooter
	SetActorEnableCollision(false);
}

void AGuidedProjectile::SetTarget(AActor* InTarget)
{
	Target = InTarget;
}

// Called when the game starts or when spawned
void AGuidedProjectile::BeginPlay()
{
	Super::BeginPlay();

	// enable collision after a moment of flight
	FTimerHandle CollisionTimer;
	GetWorldTimerManager().SetTimer(CollisionTimer, [this]
	{
		SetActorEnableCollision(true);
	}, 0.5f, false);
}

void AGuidedProjectile::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	// Explode after any collision 
	Explode();
}

void AGuidedProjectile::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other,
                                  class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation,
                                  FVector HitNormal,
                                  FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	// Explode after any collision 
	Explode();
}

void AGuidedProjectile::OnExpireTimer()
{
	// Explode after timer expires
	Explode();
}

void AGuidedProjectile::Explode()
{
	// sweep for objects in a sphere around the projectile
	TArray<FOverlapResult> OutHits;

	// check around current location - the explosion center
	FVector Center = GetActorLocation();

	// no need to rotate the sphere
	FQuat Rotation = FQuat::Identity;

	// check for collisions with damagables
	FCollisionObjectQueryParams ObjectParams;
	ObjectParams.AddObjectTypesToQuery(ECC_Pawn);
	ObjectParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	// use a sphere shape
	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(ExplosionRadius);

	// ignore self
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	if (GetWorld()->OverlapMultiByObjectType(OutHits, Center, Rotation, ObjectParams, CollisionShape, QueryParams))
	{
		// iterate over each object hit
		for (const FOverlapResult& CurrentHit : OutHits)
		{
			// check if we've hit a damageable actor
			ICombatDamageable* Damageable = Cast<ICombatDamageable>(CurrentHit.GetActor());

			if (Damageable)
			{
				// Apply knockback to the center of the actor
				FVector HitLocation = CurrentHit.GetActor()->GetActorLocation();

				// knock away from the center of explosion
				const FVector Impulse = (HitLocation - Center).GetSafeNormal() * ExplosionImpulse;

				// pass the damage event to the actor
				Damageable->ApplyDamage(ExplosionDamage, this, HitLocation, Impulse);
			}
		}
	}

	// Destroy the projectile
	Destroy();
}

// Called every frame
void AGuidedProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// find the desired direction to face
	FVector CurrentDirection = GetActorForwardVector();
	FVector GoalDirection = (Target->GetActorLocation() - GetActorLocation()).GetSafeNormal();

	// find the angle to rotate by, limited by rotation speed
	float LimitedRadian = 2 * PI * RotationSpeed * DeltaTime / 360;
	float FullRadian = FMath::Acos(FVector::DotProduct(CurrentDirection, GoalDirection));
	float Radian = FMath::Min(LimitedRadian, FullRadian);

	// rotate towards target
	FVector Axis = FVector::CrossProduct(CurrentDirection, GoalDirection);
	FQuat Rotation{Axis, Radian};
	AddActorWorldRotation(Rotation);

	// move the projectile forward
	FVector Translation{GetActorForwardVector() * DeltaTime * Velocity};
	SetActorLocation(GetActorLocation() + Translation);
}
