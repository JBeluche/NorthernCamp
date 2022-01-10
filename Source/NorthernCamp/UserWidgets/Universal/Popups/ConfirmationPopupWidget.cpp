// Copyright Creating Mountains!


#include "NorthernCamp/UserWidgets/Universal/Popups/ConfirmationPopupWidget.h"

#include "Components/Button.h"

bool UConfirmationPopupWidget::Initialize()
{
	bool Success = Super::Initialize();
	
	B_Cancel->OnClicked.AddDynamic(this, &UConfirmationPopupWidget::Cancel);
	
	return true;
}


void UConfirmationPopupWidget::Cancel()
{
	RemoveFromViewport();
}
