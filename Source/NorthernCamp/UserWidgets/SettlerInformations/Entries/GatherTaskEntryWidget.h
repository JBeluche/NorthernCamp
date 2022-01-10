// Copyright Creating Mountains!

// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GatherTaskEntryWidget.generated.h"

class ABuildingBaseActor;
class UTextBlock;
class UImage;
class UButton;
class ANorthernCampPlayerController;

enum class EResourceType : uint8;

UCLASS()
class NORTHERNCAMP_API UGatherTaskEntryWidget : public UUserWidget
{
	GENERATED_BODY()

	
private:
	virtual bool Initialize();
	UUserWidget* AcceptPopupWidget;
	ANorthernCampPlayerController* PlayerController;


public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TX_Name;

	UPROPERTY(meta = (BindWidget))
	UImage* IMG_Icon;

	UPROPERTY(meta = (BindWidget))
	UButton* B_ThisSelected;
	
	EResourceType ResourceToGather;

	UFUNCTION()
	void Selected();

	UFUNCTION()
	void Accepted();	
};
