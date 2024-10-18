// Copyright SyntaxSultan

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "EFDAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties(){}

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;

	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;

	UPROPERTY()
	AController* SourceController = nullptr;

	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;

	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;

	UPROPERTY()
	AController* TargetController = nullptr;

	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};

template<class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;

UCLASS()
class ESCAPEFROMDUNGEON_API UEFDAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UEFDAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;
	
	/* Vital Attributes */
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category="Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UEFDAttributeSet, Health);
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category="Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UEFDAttributeSet, Mana);
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

	/* Meta Attributes */

	UPROPERTY(BlueprintReadOnly, Category="Meta Attributes")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UEFDAttributeSet, IncomingDamage);
	
	/* Primary Attributes*/

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category="Primary Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UEFDAttributeSet, Strength);
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category="Primary Attributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UEFDAttributeSet, Intelligence);
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Resilience, Category="Primary Attributes")
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UEFDAttributeSet, Resilience);
	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldResilience);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vigor, Category="Primary Attributes")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UEFDAttributeSet, Vigor);
	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Charisma, Category="Primary Attributes")
	FGameplayAttributeData Charisma;
	ATTRIBUTE_ACCESSORS(UEFDAttributeSet, Charisma);
	UFUNCTION()
	void OnRep_Charisma(const FGameplayAttributeData& OldCharisma);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Perception, Category="Primary Attributes")
	FGameplayAttributeData Perception;
	ATTRIBUTE_ACCESSORS(UEFDAttributeSet, Perception);
	UFUNCTION()
	void OnRep_Perception(const FGameplayAttributeData& OldPerception);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Luck, Category="Primary Attributes")
	FGameplayAttributeData Luck;
	ATTRIBUTE_ACCESSORS(UEFDAttributeSet, Luck);
	UFUNCTION()
	void OnRep_Luck(const FGameplayAttributeData& OldLuck);
	
	/* Secondary Attributes */
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category="Secondary Attributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UEFDAttributeSet, Armor);
	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorPenetration, Category="Secondary Attributes")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UEFDAttributeSet, ArmorPenetration);
	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BlockChance, Category="Secondary Attributes")
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(UEFDAttributeSet, BlockChance);
	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitChance, Category="Secondary Attributes")
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(UEFDAttributeSet, CriticalHitChance);
	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitDamage, Category="Secondary Attributes")
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(UEFDAttributeSet, CriticalHitDamage);
	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitResistance, Category="Secondary Attributes")
	FGameplayAttributeData CriticalHitResistance;
	ATTRIBUTE_ACCESSORS(UEFDAttributeSet, CriticalHitResistance);
	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegeneration, Category="Secondary Attributes")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UEFDAttributeSet, HealthRegeneration);
	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegeneration, Category="Secondary Attributes")
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UEFDAttributeSet, ManaRegeneration);
	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category="Secondary Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UEFDAttributeSet, MaxHealth);
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category="Secondary Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UEFDAttributeSet, MaxMana);
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

	/* Resistance Attributes */
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_FireResistance, Category="Resistance Attributes")
	FGameplayAttributeData FireResistance;
	ATTRIBUTE_ACCESSORS(UEFDAttributeSet, FireResistance);
	UFUNCTION()
	void OnRep_FireResistance(const FGameplayAttributeData& OldFireResistance) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_LightningResistance, Category="Resistance Attributes")
	FGameplayAttributeData LightningResistance;
	ATTRIBUTE_ACCESSORS(UEFDAttributeSet, LightningResistance);
	UFUNCTION()
	void OnRep_LightningResistance(const FGameplayAttributeData& OldLightningResistance) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArcaneResistance, Category="Resistance Attributes")
	FGameplayAttributeData ArcaneResistance;
	ATTRIBUTE_ACCESSORS(UEFDAttributeSet, ArcaneResistance);
	UFUNCTION()
	void OnRep_ArcaneResistance(const FGameplayAttributeData& OldArcaneResistance) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PhysicalResistance, Category="Resistance Attributes")
	FGameplayAttributeData PhysicalResistance;
	ATTRIBUTE_ACCESSORS(UEFDAttributeSet, PhysicalResistance);
	UFUNCTION()
	void OnRep_PhysicalResistance(const FGameplayAttributeData& OldPhysicalResistance) const;
	
private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
	void ShowFloatingText(const FEffectProperties& Props, float Damage, bool bBlockedHit, bool bCriticalHit) const;
};
