// Copyright SyntaxSultan


#include "UI/Widgets/EFDUserWidget.h"

void UEFDUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
