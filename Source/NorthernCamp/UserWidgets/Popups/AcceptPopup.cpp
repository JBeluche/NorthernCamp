// Copyright Creating Mountains!


#include "NorthernCamp/UserWidgets/Popups/AcceptPopup.h"

bool UAcceptPopup::Initialize()
{
	bool Success = Super::Initialize();


	B_Cancel->OnClicked.AddDynamic(this, &UAcceptPopup::Cancel);

	
	return true;
}


void UAcceptPopup::Cancel()
{
	RemoveFromViewport();
	/*this->BeginDestroy();
	this->FinishDestroy();*/
}