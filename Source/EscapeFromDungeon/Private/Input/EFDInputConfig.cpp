// Copyright SyntaxSultan


#include "Input/EFDInputConfig.h"

const UInputAction* UEFDInputConfig::FindAbilityInputActionWithTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const FEFDInputAction& EFDInputAction : AbilityInputActions)
	{
		if (EFDInputAction.InputAction && EFDInputAction.InputTag.MatchesTagExact(InputTag))
		{
			return EFDInputAction.InputAction;
		}
	}
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find AbilityInputAction for InputTag [%s], on InputConfig [%s]"), *InputTag.ToString(), *GetNameSafe(this));
	}
	return nullptr;
}
