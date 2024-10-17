// Copyright SyntaxSultan

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "EFDAbilitySystemGlobals.generated.h"

UCLASS()
class ESCAPEFROMDUNGEON_API UEFDAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()
	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
};
