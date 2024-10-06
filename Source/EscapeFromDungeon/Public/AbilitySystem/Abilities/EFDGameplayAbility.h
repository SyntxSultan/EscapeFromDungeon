// Copyright SyntaxSultan

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "EFDGameplayAbility.generated.h"

UCLASS()
class ESCAPEFROMDUNGEON_API UEFDGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, Category="Input")
	FGameplayTag StartupInputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Damage")
	FScalableFloat Damage = 1.f;
};
