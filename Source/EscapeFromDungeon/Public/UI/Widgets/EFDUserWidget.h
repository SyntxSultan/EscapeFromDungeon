// Copyright SyntaxSultan

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EFDUserWidget.generated.h"

UCLASS()
class ESCAPEFROMDUNGEON_API UEFDUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
	
};
