// Copyright SyntaxSultan


#include "AbilitySystem/EFDAbilitySystemGlobals.h"
#include "EFDAbilityTypes.h"

FGameplayEffectContext* UEFDAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FEFDGameplayEffectContext();
}
