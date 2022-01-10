// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ConfirmationPopupWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class NORTHERNCAMP_API UConfirmationPopupWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	virtual bool Initialize();

public:
	UPROPERTY(meta = (BindWidget))
	UButton* B_Accept;

	UPROPERTY(meta = (BindWidget))
	UButton* B_Cancel;

	UFUNCTION()
	void Cancel();
		
};
