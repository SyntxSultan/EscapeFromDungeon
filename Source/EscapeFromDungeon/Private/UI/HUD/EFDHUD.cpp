// Copyright SyntaxSultan


#include "UI/HUD/EFDHUD.h"

#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/Widgets/EFDUserWidget.h"

UOverlayWidgetController* AEFDHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallbacksToDependencies();
		return  OverlayWidgetController;
	}
	return  OverlayWidgetController;
}

void AEFDHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay widget class is not set, please fill out in BP_EFDHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay widget controller class is not set, please fill out in BP_EFDHUD"));
	
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);		//Creating Blueprint version of OverlayWidget
	OverlayWidget = Cast<UEFDUserWidget>(Widget);														//Casting it to UEFDUserWidget

	FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);									//Constructing a WidgetControllerParams
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);	//Creating a OverlayWidgetController
	
	OverlayWidget->SetWidgetController(WidgetController);												//Adding OverlayWidgetController to OverlayWidget
	WidgetController->BroadcastInitialValues();

    Widget->AddToViewport();
}