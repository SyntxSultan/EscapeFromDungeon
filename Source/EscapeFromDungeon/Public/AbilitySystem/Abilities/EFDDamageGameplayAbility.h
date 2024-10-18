// Copyright SyntaxSultan

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/EFDGameplayAbility.h"
#include "EFDDamageGameplayAbility.generated.h"

UCLASS()
class ESCAPEFROMDUNGEON_API UEFDDamageGameplayAbility : public UEFDGameplayAbility
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;
	
	UPROPERTY(EditDefaultsOnly, Category="Damage")
	TMap<FGameplayTag, FScalableFloat> DamageTypes;
};
