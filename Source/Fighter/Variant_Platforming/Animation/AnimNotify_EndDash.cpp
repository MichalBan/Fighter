// Copyright Epic Games, Inc. All Rights Reserved.


#include "AnimNotify_EndDash.h"

#include "CombatCharacter.h"
#include "PlatformingCharacter.h"
#include "Components/SkeletalMeshComponent.h"

void UAnimNotify_EndDash::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	// cast the owner to the attacker interface
	if (ACombatCharacter* CombatCharacter = Cast<ACombatCharacter>(MeshComp->GetOwner()))
	{
		// tell the actor to end the dash
		CombatCharacter->EndDash();
	}
}

FString UAnimNotify_EndDash::GetNotifyName_Implementation() const
{
	return FString("End Dash");
}
