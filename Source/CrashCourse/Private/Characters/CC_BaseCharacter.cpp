// Fill out your copyright notice in the Description page of Project Settings.


#include "CrashCourse/Public/Characters/CC_BaseCharacter.h"


ACC_BaseCharacter::ACC_BaseCharacter()
{
	
	PrimaryActorTick.bCanEverTick = false;

	// Ensure animations and bone transforms update even when the mesh isn't visible (needed for accurate bone data in gameplay logic)
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}

UAbilitySystemComponent* ACC_BaseCharacter::GetAbilitySystemComponent() const
{
	return nullptr;
}





