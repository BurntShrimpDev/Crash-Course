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

	AttributeWidget->OnAttributeChange(Pair, AttributeSet.Get()); // for initial values

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Key).AddLambda(
		[this, AttributeWidget, &Pair](const FOnAttributeChangeData& AttributeChangeData)
		{
			AttributeWidget->OnAttributeChange(Pair, AttributeSet.Get()); // for live gameplay changes
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
