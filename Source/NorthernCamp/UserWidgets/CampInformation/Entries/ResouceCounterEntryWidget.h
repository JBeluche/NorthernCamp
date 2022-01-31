// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ResouceCounterEntryWidget.generated.h"

class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS()
class NORTHERNCAMP_API UResouceCounterEntryWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TX_Amount;

	UPROPERTY(meta = (BindWidget))
	UImage* IMG_Icon;

	//Not using this yet. To display total amount of resources carried by settlers.
	/*UPROPERTY(meta = (BindWidget))
	UImage* TX_AmountSettlers;*/

	
	
};
