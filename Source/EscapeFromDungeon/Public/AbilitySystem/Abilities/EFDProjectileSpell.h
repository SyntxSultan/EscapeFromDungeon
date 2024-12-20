// Copyright SyntaxSultan

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/EFDDamageGameplayAbility.h"
#include "EFDProjectileSpell.generated.h"

class AEFDProjectile;
class UGameplayEffect;

UCLASS()
class ESCAPEFROMDUNGEON_API UEFDProjectileSpell : public UEFDDamageGameplayAbility
{
	GENERATED_BODY()
	
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;	

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AEFDProjectile> ProjectileClass;

	UFUNCTION(BlueprintCallable)
	void SpawnProjectile(const FVector& TargetLocation);

};
