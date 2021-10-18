// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NorthernCamp/Characters/CharacterHero.h"

#include "NorthernCampPlayerController.generated.h"
//Classes
class UUserWidget;
class ALooseCameraPawn;

class ACharacterBase;
class ACharacterSettler;
class UScrollBox;

//Enums 
UENUM(BlueprintType)
enum class ECurrentPawn : uint8 
{
	ArenCharacter UMETA(DisplayName = "Aren Character"),
	Camp UMETA(DisplayName = "Camp"),
	
};

UENUM(BlueprintType)
enum class ECurrentUI : uint8 
{
	SettlersInfo UMETA(DisplayName = "Information Settler"),
};

UCLASS()
class ANorthernCampPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ANorthernCampPlayerController();

	void SwitchPawn(ECurrentPawn NewPawn);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECurrentPawn CurrentPawnEnum;

	UUserWidget* GetDialogWidget();
	void SetSelectedHero(EHero CharacterHeroEnum);

	
	ACharacterSettler* SelectedSettler;


protected:

	virtual void BeginPlay() override;
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

private:

	//Varaibles C++
	TSubclassOf<class UUserWidget> LooseCameraUserWidget;
	TSubclassOf<class UUserWidget> CampControlClass;
	TSubclassOf<class UUserWidget> DialogWidget;
	TSubclassOf<class UUserWidget> SettlerInfoUserWidget;
	
	UUserWidget* Controls;
	AActor* MyOwner;
	
	//AArenCharacter* ControlledCharater;

	//Varialbes Blueprint
	//ACampPawn* CampPawn;
	ALooseCameraPawn* LooseCameraPawn;
	ACharacterHero* SelectedHero;


	FVector2D PreviousTouchLocation;
	FVector2D NewTouchLocation;
	bool bFingerReleased;
	bool bIsFingerTouching;
	float FingerTouchDuration;
	FHitResult LastTouchHitResults;
	FVector TargetLocation;
	bool bTargetLocationSet;

	bool bCameraIsMoving;
	int FingerTapAmount;
	float LastTimeFingerTouched;
	float Time;
	bool FingerTouched;
	float StartingLocationFingerX;
	float StartingLocationFingerY;

	bool bIsInMenu;

	UScrollBox* CurrentScrollBar;
	
	//Functions
	void SetNewOwner();
	void DoubleTapTouchCondition();
	void MoveCameraAccordingToFinger();
	void KeepCameraInHeroBounds(float DeltaTime);
	void SelectSettlerCondition();
	void UpdateUI(ECurrentUI NewCurrentUI);

	void FingerTouchHandler(float DeltaTime);

};


