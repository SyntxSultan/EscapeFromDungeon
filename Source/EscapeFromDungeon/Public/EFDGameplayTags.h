// Copyright SyntaxSultan

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 *	Singleton containing native Gameplay Tags
 */

struct FEFDGameplayTags
{
public:
    static const FEFDGameplayTags& Get() { return GameplayTags; }
    static void InitializeNativeGameplayTags();

	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Resilience;
	FGameplayTag Attributes_Primary_Vigor;
	FGameplayTag Attributes_Primary_Charisma;
	FGameplayTag Attributes_Primary_Perception;
	FGameplayTag Attributes_Primary_Luck;
	
	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	FGameplayTag Attributes_Secondary_CriticalHitDamage;
	FGameplayTag Attributes_Secondary_CriticalHitResistance;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;
 
private:
	static FEFDGameplayTags GameplayTags;
};
