// Copyright SyntaxSultan


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/EFDAbilitySystemComponent.h"
#include "AbilitySystem/EFDAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UEFDAttributeSet* EFDAttributeSet = CastChecked<UEFDAttributeSet>(AttributeSet);
	
	OnHealthChanged.Broadcast(EFDAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(EFDAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(EFDAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(EFDAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UEFDAttributeSet* EFDAttributeSet = CastChecked<UEFDAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(EFDAttributeSet->GetHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		OnHealthChanged.Broadcast(Data.NewValue);
	});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(EFDAttributeSet->GetMaxHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		OnMaxHealthChanged.Broadcast(Data.NewValue);
	});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(EFDAttributeSet->GetManaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		OnManaChanged.Broadcast(Data.NewValue);
	});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(EFDAttributeSet->GetMaxManaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		OnMaxManaChanged.Broadcast(Data.NewValue);
	});
	Cast<UEFDAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda([this](const FGameplayTagContainer& AssetTags)
	{
		for (const FGameplayTag& Tag : AssetTags)
		{
			FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
			if (Tag.MatchesTag(MessageTag))
			{
				const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
				MessageWidgetRowDelegate.Broadcast(*Row);
			}
		}
	});
}