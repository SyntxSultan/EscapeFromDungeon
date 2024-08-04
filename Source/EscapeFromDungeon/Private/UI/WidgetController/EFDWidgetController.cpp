// Copyright SyntaxSultan


#include "UI/WidgetController/EFDWidgetController.h"

void UEFDWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WidgetControllerParams)
{
	PlayerController = WidgetControllerParams.PlayerController;
	PlayerState = WidgetControllerParams.PlayerState;
	AbilitySystemComponent = WidgetControllerParams.AbilitySystemComponent;
	AttributeSet = WidgetControllerParams.AttributeSet;
}

void UEFDWidgetController::BroadcastInitialValues()
{
	// Fill in child
}

void UEFDWidgetController::BindCallbacksToDependencies()
{
	// Fill in child
}
