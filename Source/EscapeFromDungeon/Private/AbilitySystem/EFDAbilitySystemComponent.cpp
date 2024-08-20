// Copyright SyntaxSultan


#include "AbilitySystem/EFDAbilitySystemComponent.h"

void UEFDAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UEFDAbilitySystemComponent::EffectApplied);
}

void UEFDAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	for (const FGameplayTag& Tag : TagContainer)
	{
		const FString Msg = FString::Printf(TEXT("GE Effect: %s"), *Tag.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, Msg);
	}
}
