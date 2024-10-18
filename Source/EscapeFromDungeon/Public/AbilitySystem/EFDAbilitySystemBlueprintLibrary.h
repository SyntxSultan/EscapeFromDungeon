// Copyright SyntaxSultan

#pragma once

#include "CoreMinimal.h"
#include "Data/CharacterClassInfo.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EFDAbilitySystemBlueprintLibrary.generated.h"

struct FGameplayEffectContextHandle;
class UAbilitySystemComponent;
class UAttributeMenuWidgetController;
class UOverlayWidgetController;

UCLASS()
class ESCAPEFROMDUNGEON_API UEFDAbilitySystemBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category="EFDAbilitySystemBlueprintLibrary|WidgetController")
    static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);
	UFUNCTION(BlueprintPure, Category="EFDAbilitySystemBlueprintLibrary|WidgetController")
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category="EFDAbilitySystemBlueprintLibrary|CharacterClassDefaults")
	static void InitializeDefaultAttributes(const UObject* WorldContextObject, const ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* AbilitySystemComponent);

	UFUNCTION(BlueprintCallable, Category="EFDAbilitySystemBlueprintLibrary|CharacterClassDefaults")
	static void GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* AbilitySystemComponent);

	UFUNCTION(BlueprintCallable, Category="EFDAbilitySystemBlueprintLibrary|CharacterClassDefaults")
	static UCharacterClassInfo* GetCharacterClassInfo(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category="EFDAbilitySystemBlueprintLibrary|GameplayEffects")
	static bool IsBlockedHit(const FGameplayEffectContextHandle& ContextHandle);

	UFUNCTION(BlueprintPure, Category="EFDAbilitySystemBlueprintLibrary|GameplayEffects")
	static bool IsCriticalHit(const FGameplayEffectContextHandle& ContextHandle);

	UFUNCTION(BlueprintCallable, Category="EFDAbilitySystemBlueprintLibrary|GameplayEffects")
	static void SetIsBlockedHit(UPARAM(ref) FGameplayEffectContextHandle& ContextHandle, bool bInIsBlockedHit);

	UFUNCTION(BlueprintCallable, Category="EFDAbilitySystemBlueprintLibrary|GameplayEffects")
	static void SetIsCriticalHit(UPARAM(ref) FGameplayEffectContextHandle& ContextHandle, bool bInIsCriticalHit);
};
