// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UHeroBarWidget.generated.h"

class ANorthernCampPlayerController;
UCLASS()
class NORTHERNCAMP_API UUHeroBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual bool Initialize();
	
private:

	ANorthernCampPlayerController* PlayerController;

	
	//UPROPERTY
	UPROPERTY(meta = (BindWidget))
	class UButton* B_Will;

	UPROPERTY(meta = (BindWidget))
	class UButton* B_Hunter;

	UPROPERTY(meta = (BindWidget))
    class UButton* B_Trader;

    UPROPERTY(meta = (BindWidget))
    class UButton* B_SeaRaider;

	UPROPERTY(meta = (BindWidget))
	class UButton* B_MineDweller;

	UPROPERTY(meta = (BindWidget))
	class UButton* B_Druida;

	UPROPERTY(meta = (BindWidget))
	class UButton* B_Alchemist;

	UPROPERTY(meta = (BindWidget))
	class UButton* B_Occultist;

	//UFUNCTION
	UFUNCTION()
	void SwitchToWill();

	UFUNCTION()
	void SwitchToTrader();

	UFUNCTION()
	void SwitchToHunter();
	
	UFUNCTION()
	void SwitchToSeaRaider();

	UFUNCTION()
	void SwitchToMineDweller();

	UFUNCTION()
	void SwitchToDruida();
	
	UFUNCTION()
	void SwitchToAlchemist();

	UFUNCTION()
	void SwitchToOccultist();

};
