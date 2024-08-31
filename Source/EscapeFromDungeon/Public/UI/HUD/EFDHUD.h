// Copyright SyntaxSultan

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "EFDHUD.generated.h"

class UAttributeMenuWidgetController;
class UAbilitySystemComponent;
class UAttributeSet;
struct FWidgetControllerParams;
class UOverlayWidgetController;
class UEFDUserWidget;

UCLASS()
class ESCAPEFROMDUNGEON_API AEFDHUD : public AHUD
{
	GENERATED_BODY()
public:
	
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);
	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams);
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

private:
	UPROPERTY()
	TObjectPtr<UEFDUserWidget> OverlayWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UEFDUserWidget> OverlayWidgetClass;
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UEFDUserWidget> AttributeMenuWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UEFDUserWidget> AttributeMenuWidgetClass;
	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;
};
