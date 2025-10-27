// Copyright Callum Brogan.


#include "UI/CC_WidgetComponent.h"

#include "AbilitySystem/CC_AbilitySystemComponent.h"
#include "AbilitySystem/CC_AttributeSet.h"
#include "Characters/CC_BaseCharacter.h"


void UCC_WidgetComponent::BeginPlay()
{
	Super::BeginPlay();
	InitAbilitySystemData();
	if (!bIsASCInitialized())
	{
		CrashCharacter->OnASCInitialized.AddDynamic(this, &ThisClass::OnASCInitialized);
		return;
	}

	InitialAttributesDelegate();
}

void UCC_WidgetComponent::InitAbilitySystemData()
{
	CrashCharacter = Cast<ACC_BaseCharacter>(GetOwner());
	AttributeSet = Cast<UCC_AttributeSet>(CrashCharacter->GetAttributeSet());
	AbilitySystemComponent = Cast<UCC_AbilitySystemComponent>(CrashCharacter->GetAbilitySystemComponent());
}

bool UCC_WidgetComponent::bIsASCInitialized() const
{
	return AbilitySystemComponent.IsValid() && AttributeSet.IsValid();
}

void UCC_WidgetComponent::InitialAttributesDelegate()
{
	if (!AttributeSet->bAttributesInitialized)
	{
		AttributeSet->OnAttributesInitialized.AddDynamic(this, &ThisClass::UCC_WidgetComponent::BindToAttributeChanges);
	}
	else
	{
		BindToAttributeChanges();
	}
}

void UCC_WidgetComponent::OnASCInitialized(UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	AbilitySystemComponent = Cast<UCC_AbilitySystemComponent>(CrashCharacter->GetAbilitySystemComponent());
	AttributeSet = Cast<UCC_AttributeSet>(CrashCharacter->GetAttributeSet());

	if (!bIsASCInitialized()) return;
	InitialAttributesDelegate();
	
}

void UCC_WidgetComponent::BindToAttributeChanges()
{
	//Todo: Listen for changes for gameplay Attributes and update our widget accordingly. 
}
