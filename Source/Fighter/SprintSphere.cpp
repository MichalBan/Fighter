// Fill out your copyright notice in the Description page of Project Settings.


#include "SprintSphere.h"

#include "CombatAttacker.h"
#include "CombatDamageable.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"

// Sets default values
ASprintSphere::ASprintSphere()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	Collider->SetupAttachment(RootComponent);
	Collider->SetSphereRadius(100);
}

// Called when the game starts or when spawned
void ASprintSphere::BeginPlay()
{
	Super::BeginPlay();
}

void ASprintSphere::SetOwner(AActor* NewOwner)
{
	Super::SetOwner(NewOwner);

	// prevent owning character and the sphere from colliding
	Collider->IgnoreActorWhenMoving(NewOwner, true);
	if (ACharacter* Character = Cast<ACharacter>(NewOwner))
	{
		Character->GetCapsuleComponent()->IgnoreActorWhenMoving(this, true);
	}
}

void ASprintSphere::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp,
                              bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse,
                              const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	// cast the collided actor to a damageable actor
	if (ICombatDamageable* Damageable = Cast<ICombatDamageable>(Other))
	{
		// knock upwards and away from the impact normal
		const FVector Impulse = HitNormal * -CollisionImpulse + FVector::UpVector * LaunchImpulse;
		// pass the damage event to the actor
		Damageable->ApplyDamage(CollisionDamage, this, HitLocation, Impulse);
	}
}

// Called every frame
void ASprintSphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
