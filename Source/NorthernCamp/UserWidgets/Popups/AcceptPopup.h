// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "AcceptPopup.generated.h"

/**
 * 
 */
UCLASS()
class NORTHERNCAMP_API UAcceptPopup : public UUserWidget
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
