// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Controllers/UIController.h"
#include "GameFramework/PlayerController.h"
#include "NorthernCamp/Characters/CharacterHero.h"

#include "NorthernCampPlayerController.generated.h"
class UNavigationSystemV1;
class ACampCameraPawn;
class UUserWidget;
class ALooseCameraPawn;
class ACharacterBase;
class ACharacterSettler;
class UScrollBox;

//Enums 
UENUM(BlueprintType)
enum class ECurrentPawn : uint8 
{
	LooseCamera UMETA(DisplayName = "Aren Character"),
	Camp UMETA(DisplayName = "Camp"),
	
};

UENUM(BlueprintType)
enum class ECurrentCampStance : uint8 
{
	Building UMETA(DisplayName = "Building"),
	Battle UMETA(DisplayName = "Battle"),
	
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

	//Public variables
	ACharacterSettler* SelectedSettler;
	UUIController* UIController;

	AResourceController* ResourceController;

	//Public functinos
	void ResetControlls();
	bool bSliderBugActive = false;


protected:

	virtual void BeginPlay() override;
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	int32 i = 0;

private:

	//Private variables
	AActor* MyOwner;

	UPROPERTY()
	UNavigationSystemV1*  NavigationSystemv1;

	ACampCameraPawn* CampCameraPawn;
	ALooseCameraPawn* LooseCameraPawn;
	ACharacterHero* SelectedHero;
	ACharacterHero* TouchedHero;

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
	float BugLocationY;
	float BugLocationX;
	int32  SliderBuggedTouchEventCount = 0;




	
	//Functions
	void SetNewOwner();
	void DoubleTapTouchCondition();
	void MoveCameraAccordingToFinger();
	void KeepCameraInHeroBounds(float DeltaTime);
	void SelectSettlerCondition();

	void FingerTouchHandler(float DeltaTime);

};


