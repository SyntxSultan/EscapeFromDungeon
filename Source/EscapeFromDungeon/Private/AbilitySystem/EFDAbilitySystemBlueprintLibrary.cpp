// Copyright SyntaxSultan


#include "AbilitySystem/EFDAbilitySystemBlueprintLibrary.h"

#include "Game/EFDGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Player/EFDPlayerState.h"
#include "UI/HUD/EFDHUD.h"
#include "UI/WidgetController/EFDWidgetController.h"

UOverlayWidgetController* UEFDAbilitySystemBlueprintLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AEFDHUD* EFDHUD = Cast<AEFDHUD>(PC->GetHUD()))
		{
			AEFDPlayerState* PS = PC->GetPlayerState<AEFDPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams Params(PC, PS, ASC, AS);
			return EFDHUD->GetOverlayWidgetController(Params);
		}
	}
	return nullptr;
}

UAttributeMenuWidgetController* UEFDAbilitySystemBlueprintLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AEFDHUD* EFDHUD = Cast<AEFDHUD>(PC->GetHUD()))
		{
			AEFDPlayerState* PS = PC->GetPlayerState<AEFDPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams Params(PC, PS, ASC, AS);
			return EFDHUD->GetAttributeMenuWidgetController(Params);
		}
	}
	return nullptr;
}

void UEFDAbilitySystemBlueprintLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject, const ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* AbilitySystemComponent)
{
	AActor* AvatarActor = AbilitySystemComponent->GetAvatarActor();
	const UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	const FCharacterClassDefaultInfo DefaultInfo = GetCharacterClassInfo(WorldContextObject)->GetCharacterClassInfo(CharacterClass);

	FGameplayEffectContextHandle PrimaryEffectContext = AbilitySystemComponent->MakeEffectContext();
	PrimaryEffectContext.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle PrimaryEffectSpec = AbilitySystemComponent->MakeOutgoingSpec(DefaultInfo.PrimaryAttributes, Level, PrimaryEffectContext);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*PrimaryEffectSpec.Data.Get());

	FGameplayEffectContextHandle SecondaryEffectContext = AbilitySystemComponent->MakeEffectContext();
	SecondaryEffectContext.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle SecondaryEffectSpec = AbilitySystemComponent->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributes, Level, SecondaryEffectContext);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SecondaryEffectSpec.Data.Get());

	FGameplayEffectContextHandle VitalEffectContext = AbilitySystemComponent->MakeEffectContext();
	VitalEffectContext.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle VitalEffectSpec = AbilitySystemComponent->MakeOutgoingSpec(CharacterClassInfo->VitalAttributes, Level, VitalEffectContext);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*VitalEffectSpec.Data.Get());
}

void UEFDAbilitySystemBlueprintLibrary::GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* AbilitySystemComponent)
{
	const UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	for (TSubclassOf<UGameplayAbility> Ability : CharacterClassInfo->Abilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability, 1.f);
		AbilitySystemComponent->GiveAbility(AbilitySpec);
	}
}

UCharacterClassInfo* UEFDAbilitySystemBlueprintLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	AEFDGameModeBase* EFDGameMode = Cast<AEFDGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (!EFDGameMode) return nullptr;
	return EFDGameMode->CharacterClassInfo;
}
