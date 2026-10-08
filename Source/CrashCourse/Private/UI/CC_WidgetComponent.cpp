// Copyright Callum Brogan.


#include "UI/CC_WidgetComponent.h"

#include "AbilitySystem/CC_AbilitySystemComponent.h"
#include "AbilitySystem/CC_AttributeSet.h"
#include "Blueprint/WidgetTree.h"
#include "Characters/CC_BaseCharacter.h"
#include "UI/CC_AttributeWidget.h"


void UCC_WidgetComponent::BeginPlay()
{
	Super::BeginPlay();
	InitAbilitySystemData();
	if (!CrashCharacter.IsValid()) return; // Only works on CC_BaseCharacter owners
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
	if (!CrashCharacter.IsValid()) return;
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
		AttributeSet->OnAttributesInitialized.AddDynamic(this, &ThisClass::BindToAttributeChanges);
	}
	else
	{
		BindToAttributeChanges();
	}
}

void UCC_WidgetComponent::BindWidgetToAttributeChange(UWidget* WidgetObject,
                                                      const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const
{
	UCC_AttributeWidget* AttributeWidget = Cast<UCC_AttributeWidget>(WidgetObject);
	if (!IsValid(AttributeWidget)) return; // Only care about CC Attribute Widgets
	if (!AttributeWidget->MatchesAttributes(Pair)) return; // Only subscribe for matching Attributes
	AttributeWidget->AvatarActor = CrashCharacter;

	AttributeWidget->OnAttributeChange(Pair, AttributeSet.Get(), 0.f); // for initial values

	// The ASC can outlive this component (the player's lives on the PlayerState), so bind weakly to this component
	// and hold the widget weakly too
	TWeakObjectPtr<UCC_AttributeWidget> WeakAttributeWidget = AttributeWidget;
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Key).AddWeakLambda(this,
		[this, WeakAttributeWidget, &Pair](const FOnAttributeChangeData& AttributeChangeData)
		{
			if (!WeakAttributeWidget.IsValid()) return;
			WeakAttributeWidget->OnAttributeChange(Pair, AttributeSet.Get(), AttributeChangeData.OldValue); // for live gameplay changes
		});
}

void UCC_WidgetComponent::OnASCInitialized(UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	AbilitySystemComponent = Cast<UCC_AbilitySystemComponent>(ASC);
	AttributeSet = Cast<UCC_AttributeSet>(AS);

	if (!bIsASCInitialized()) return;
	InitialAttributesDelegate();
}

void UCC_WidgetComponent::BindToAttributeChanges()
{
	for (const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair : AttributeMap)
	{
		BindWidgetToAttributeChange(GetUserWidgetObject(), Pair); // Checking the owned widget object
		
		GetUserWidgetObject()->WidgetTree->ForEachWidget([this, &Pair](UWidget* ChildWidget)
		{
			BindWidgetToAttributeChange(ChildWidget, Pair);
		});
	}
}
