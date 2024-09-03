// Copyright SyntaxSultan

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "EFDCharacterBase.generated.h"

class UGameplayAbility;
class UGameplayEffect;
class UAttributeSet;
class UAbilitySystemComponent;

UCLASS(Abstract)
class ESCAPEFROMDUNGEON_API AEFDCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	AEFDCharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
	UPROPERTY(EditAnywhere, Category="Combat")
	FName WeaponTipSocketName;

	virtual FVector GetCombatSocketLocation() override;
	
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	virtual void InitAbilityActorInfo();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes|Initializers")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes|Initializers")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes|Initializers")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffect, float Level) const;
	void InitializeDefaultAttributes() const;

	void AddCharacterAbilities();
private:
	UPROPERTY(EditAnywhere, Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
};
