// Copyright SyntaxSultan


#include "EFDAssetManager.h"

#include "EFDGameplayTags.h"
#include "AbilitySystemGlobals.h"

const UEFDAssetManager& UEFDAssetManager::Get()
{
	check(GEngine);

	UEFDAssetManager* EFDAssetManager = Cast<UEFDAssetManager>(GEngine->AssetManager);
	return *EFDAssetManager;
}

void UEFDAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FEFDGameplayTags::InitializeNativeGameplayTags();
	UAbilitySystemGlobals::Get().InitGlobalData();
}
