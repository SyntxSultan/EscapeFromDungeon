// Copyright SyntaxSultan

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "EFDInputConfig.generated.h"

class UInputAction;

USTRUCT(BlueprintType)
struct FEFDInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
};

UCLASS()
class ESCAPEFROMDUNGEON_API UEFDInputConfig : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FEFDInputAction> AbilityInputActions;

	const UInputAction* FindAbilityInputActionWithTag(const FGameplayTag& InputTag, bool bLogNotFound = false) const;
};
