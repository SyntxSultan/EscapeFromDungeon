// Copyright SyntaxSultan

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "EFDAbilitySystemComponent.generated.h"

UCLASS()
class ESCAPEFROMDUNGEON_API UEFDAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	void AbilityActorInfoSet();
protected:
	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
};
