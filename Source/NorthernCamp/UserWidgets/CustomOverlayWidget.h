// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "CustomOverlayWidget.generated.h"

/**
 * 
 */
UCLASS()
class NORTHERNCAMP_API UCustomOverlayWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	virtual bool Initialize();

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* CanvasOverlay;
};
