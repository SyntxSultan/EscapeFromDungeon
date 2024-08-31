// Copyright SyntaxSultan

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/EFDWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

class UAttributeInfo;
struct FEFDAttributeInfo;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FEFDAttributeInfo&, Info);

UCLASS(BlueprintType, Blueprintable)
class ESCAPEFROMDUNGEON_API UAttributeMenuWidgetController : public UEFDWidgetController
{
	GENERATED_BODY()
public:
	virtual void BindCallbacksToDependencies() override;
	virtual void BroadcastInitialValues() override;

	UPROPERTY(BlueprintAssignable, Category="Gas|Attributes")
	FAttributeInfoSignature AttributeInfoDelegate;

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAttributeInfo> AttributeInfo;

private:
	void BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const;
};
