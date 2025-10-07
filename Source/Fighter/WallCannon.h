// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatActivatable.h"
#include "CombatCharacter.h"
#include "GuidedProjectile.h"
#include "GameFramework/Actor.h"
#include "WallCannon.generated.h"

UCLASS()
class FIGHTER_API AWallCannon : public AActor, public ICombatActivatable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWallCannon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Handler of shot timer
	void OnShotTimer() const;

	// Handler of move timer
	void OnMoveTimer();

	// Get the spawn location for projectile
	UFUNCTION(BlueprintImplementableEvent)
	FVector GetProjectileLocation() const;

	// Class of fired projectiles
	UPROPERTY(EditAnywhere, Category = "Shooting")
	TSubclassOf<AGuidedProjectile> ClassProjectile;

	// Cooldown between shots
	UPROPERTY(EditAnywhere, Category = "Shooting", meta = (ClampMin = 0, ClampMax = 10, Units = "s"))
	float ShotCooldown = 5.0f;

	// Target that projectiles will seek
	UPROPERTY()
	AActor* Target = nullptr;

	/** Flag to ensure this is only activated once */
	bool bHasBeenActivated = false;

	// Timer for firing projectiles
	FTimerHandle TimerShot;

	// Cube actor used for movement limits
	UPROPERTY(EditAnywhere)
	AActor* MoveArea;

	// Time between trying to move
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (ClampMin = 5, ClampMax = 50, Units = "s"))
	float MoveCooldown = 10.0f;

	// Time between trying to move
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (ClampMin = 100, ClampMax = 1000, Units = "cm/s"))
	float MoveSpeed = 500.0f;

	// Timer used for movment
	FTimerHandle TimerMove;

private:
	// Cached limits for movement
	FVector Center;
	FVector Bounds;

	// Position the cannon tries to move to
	FVector NextPosition = FVector::ZeroVector;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// ~begin ICombatActivatable interface

	/** Toggles the Cannon */
	UFUNCTION(BlueprintCallable, Category = "Activatable")
	virtual void ToggleInteraction(AActor* ActivationInstigator) override;

	/** Activates the Cannon */
	UFUNCTION(BlueprintCallable, Category = "Activatable")
	virtual void ActivateInteraction(AActor* ActivationInstigator) override;

	/** Deactivates the Cannon */
	UFUNCTION(BlueprintCallable, Category = "Activatable")
	virtual void DeactivateInteraction(AActor* ActivationInstigator) override;

	// ~end IActivatable interface
};
