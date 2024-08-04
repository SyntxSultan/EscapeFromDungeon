// Copyright SyntaxSultan


#include "UI/WidgetController/OverlayWidgetController.h"

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

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(EFDAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(EFDAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(EFDAttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(EFDAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
