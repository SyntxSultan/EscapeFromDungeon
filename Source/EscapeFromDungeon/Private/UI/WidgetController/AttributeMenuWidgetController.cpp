// Copyright SyntaxSultan


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "EFDGameplayTags.h"
#include "AbilitySystem/EFDAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	UEFDAttributeSet* AS = CastChecked<UEFDAttributeSet>(AttributeSet);
	check(AttributeInfo);
	for (auto& Pair : AS->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda([this, Pair](const FOnAttributeChangeData& Data)
		{
			BroadcastAttributeInfo(Pair.Key, Pair.Value());
		});
	}
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UEFDAttributeSet* AS = CastChecked<UEFDAttributeSet>(AttributeSet);
	check(AttributeInfo);

	for (auto& Pair : AS->TagsToAttributes)
	{
		BroadcastAttributeInfo(Pair.Key, Pair.Value());
	}
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const
{
	FEFDAttributeInfo Info = AttributeInfo->FindAttributeInfoWithTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}
