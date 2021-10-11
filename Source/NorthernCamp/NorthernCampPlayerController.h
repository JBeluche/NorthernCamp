// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NorthernCampPlayerController.generated.h"

//Classes
class UUserWidget;
class ALooseCameraPawn;
class ACharacterHero;
class ACharacterBase;


//Enums 
UENUM(BlueprintType)
enum class ECurrentPawn : uint8 
{
	ArenCharacter UMETA(DisplayName = "Aren Character"),
	Camp UMETA(DisplayName = "Camp"),
	
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


protected:

	virtual void BeginPlay() override;
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	//virtual void SetupInputComponent() override;

private:

	//Varaibles C++
	TSubclassOf<class UUserWidget> CharacterControlClass;
	TSubclassOf<class UUserWidget> CampControlClass;
	TSubclassOf<class UUserWidget> DialogWidget;
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
	
	//Functions
	void SetNewOwner();
	void DoubleTapTouchCondition();
	void MoveCameraAccordingToFinger();
	void KeepCameraInHeroBounds(float DeltaTime);

	void FingerTouchHandler(float DeltaTime);

};


