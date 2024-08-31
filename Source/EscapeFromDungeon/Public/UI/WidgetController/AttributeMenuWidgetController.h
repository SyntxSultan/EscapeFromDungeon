// Copyright SyntaxSultan

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/EFDWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

UCLASS(BlueprintType, Blueprintable)
class ESCAPEFROMDUNGEON_API UAttributeMenuWidgetController : public UEFDWidgetController
{
	GENERATED_BODY()
public:
	virtual void BindCallbacksToDependencies() override;
	virtual void BroadcastInitialValues() override;
};
