// Copyright SyntaxSultan


#include "AbilitySystem/EFDAbilitySystemBlueprintLibrary.h"
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
