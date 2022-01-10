// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CampCameraControlsWidget.generated.h"

class ANorthernCampPlayerController;
/**
 * 
 */
UCLASS()
class NORTHERNCAMP_API UCampCameraControlsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void SwitchToCharacter();
	
	UPROPERTY(meta = (BindWidget))
	class UButton* B_SwitchToLoosCameraPawn;

	ANorthernCampPlayerController* PlayerController;
	

	
};
