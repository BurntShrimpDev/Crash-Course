// Copyright Callum Brogan.


#include "AbilitySystem/Abilities/Enemy/CC_HitReact.h"

void UCC_HitReact::CacheHitDirectionVectors(AActor* Instigator)
{
	if (!IsValid(Instigator) || !IsValid(GetAvatarActorFromActorInfo())) return;

	AvatarForward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	
	const FVector AvatarLocation = GetAvatarActorFromActorInfo()->GetActorLocation();
	const FVector InstigatorLocation = Instigator->GetActorLocation();

	ToInstigator = InstigatorLocation - AvatarLocation;
	ToInstigator.Normalize();
}
