// Copyright Epic Games, Inc. All Rights Reserved.

#include "NorthernCampPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
//#include "ArenCharacter.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Engine/World.h"
#include "Blueprint/UserWidget.h"
//#include "NorthernCamp/Pawns/CampPawn.h"
#include "NorthernCamp/Pawns/LooseCameraPawn.h"
#include "NorthernCamp/Characters/CharacterHero.h"
#include "EngineUtils.h"
#include "Math/UnrealMathUtility.h"
#include "EngineUtils.h"

///////
//	
///////

ANorthernCampPlayerController::ANorthernCampPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;

	/*ConstructorHelpers::FClassFinder<UUserWidget> WBPControlsCharacter(TEXT("/Game/Blueprints/Widgets/WBP_ControlsPlayer"));
	ConstructorHelpers::FClassFinder<UUserWidget> WBPControlsCamp(TEXT("/Game/Blueprints/Widgets/WBP_ControlsCamp"));
	ConstructorHelpers::FClassFinder<UUserWidget> DialogWidgetClass(TEXT("/Game/Blueprints/Widgets/WBP_Dialog"));

	CharacterControlClass = WBPControlsCharacter.Class;
	CampControlClass = WBPControlsCamp.Class;
	DialogWidget = DialogWidgetClass.Class;*/

	//CampPawn = nullptr;
	LooseCameraPawn = nullptr;
	SelectedHero = nullptr;
}

void ANorthernCampPlayerController::BeginPlay()
{
	//Seting playable pawns.
	/*for (TActorIterator<ACampPawn> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		CampPawn = *ActorItr;
	}*/
	for (TActorIterator<ALooseCameraPawn> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		LooseCameraPawn = *ActorItr;
	}
	for (TActorIterator<ACharacterHero> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		SelectedHero = *ActorItr;
	}

	CurrentPawnEnum = ECurrentPawn::ArenCharacter;
	SetNewOwner();

	FingerTouchDuration = 0.0f;

}

void ANorthernCampPlayerController::PlayerTick(float DeltaTime)
{

	Super::PlayerTick(DeltaTime);

	//Easy way to measure time.
	Time = Time + 1.0f;

	KeepCameraInHeroBounds(DeltaTime);
	if(!bCameraIsMoving)
	{
		GetInputTouchState(ETouchIndex::Touch1, NewTouchLocation.X, NewTouchLocation.Y, bIsFingerTouching);
		FingerTouchHandler(DeltaTime);
	}
}
/*
void ANorthernCampPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	Controls = CreateWidget<UUserWidget>(this, CharacterControlClass, FName("Character Controls"));
	Controls->AddToViewport();
}

void ANorthernCampPlayerController::SwitchPawn(ECurrentPawn NewPawn)
{
	CurrentPawnEnum = NewPawn;
	if(Controls){Controls->RemoveFromViewport();}
		
		UnPossess();
	

	if (CurrentPawnEnum == ECurrentPawn::ARENCHARACTER)
	{
		Possess(MainPlayerPawn);
		SetOwner();
		//Get the player charater on the map and focus camera

		Controls = CreateWidget<UUserWidget>(this, CharacterControlClass, FName("Character Controls"));
		Controls->AddToViewport();

	}
	else if (CurrentPawnEnum == ECurrentPawn::CAMP)
	{
		Possess(CampPawn);
		SetOwner();

		Controls = CreateWidget<UUserWidget>(this, CampControlClass, FName("Camp Controls"));
		Controls->AddToViewport();

	}
	else if(CurrentPawnEnum == ECurrentPawn::DIALOG)
	{

		Possess(MainPlayerPawn);
		SetOwner();
		UE_LOG(LogTemp, Error, TEXT("Dialog is set"));

	}


}*/

void ANorthernCampPlayerController::SetNewOwner()
{
	MyOwner = Cast<AActor>(GetPawn());
}
/*
UUserWidget* ANorthernCampPlayerController::GetDialogWidget()
{
	return CreateWidget<UUserWidget>(this, DialogWidget, FName("Dialog Controls"));
}*/

void ANorthernCampPlayerController::FingerTouchHandler(float DeltaTime)
{

	/*if (CurrentPawnEnum == ECurrentPawn::CAMP)
	{
	GetInputTouchState(ETouchIndex::Touch1, NewTouchLocation.X, NewTouchLocation.Y, bIsFingerTouching);
	if (bIsFingerTouching)
	{
	if (MyOwner)
	{
	float NewRotation = PreviousTouchLocation.X - NewTouchLocation.X;

	FRotator CurrentRotation = MyOwner->GetActorRotation();

	if (PreviousTouchLocation.X == 0.0f)
	{
	NewRotation = 0.0f;
	}

	MyOwner->SetActorRotation(FRotator(CurrentRotation.Pitch, (CurrentRotation.Yaw + NewRotation), CurrentRotation.Roll));
	}
	PreviousTouchLocation = NewTouchLocation;
	}
	else
	{
	PreviousTouchLocation.X = 0.0f;
	}
	}
	else if (CurrentPawnEnum == ECurrentPawn::Hero)
	{*/

	//What to do if the finger is touching the screen
	if (bIsFingerTouching)
	{
		//This is to check the initial starting points of the finger drag
		if(FingerTouched == false)
		{
			FingerTouched = true;
			StartingLocationFingerX = NewTouchLocation.X;
			StartingLocationFingerY = NewTouchLocation.Y;
		}

		LastTimeFingerTouched = Time;
		FingerTouchDuration = (FingerTouchDuration + 1.0f);
		
		GetHitResultUnderFinger(
			ETouchIndex::Touch1,
			ECC_Pawn,
			true,
			LastTouchHitResults);

		MoveCameraAccordingToFinger();
		
	}
	else
	{

		DoubleTapTouchCondition();

		//Resetting everything to check again
		PreviousTouchLocation.X = 0.0f;
		PreviousTouchLocation.Y = 0.0f;
		FingerTouchDuration = 0.0f;

	
		//	USE THIS CODE TO SELECT SETTLERS LATER ON.
		/*if (FingerTouchDuration < 50.0f && FingerTouchDuration > 2.0f)
		{
		if (SelectedCharacter != NULL)
		{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(SelectedCharacter->GetController(), LastTouchHitResults.Location);
		}
		else if (Cast<ACharacterBase>(LastTouchHitResults.Actor))
		{
		SelectedCharacter = Cast<ACharacterBase>(LastTouchHitResults.Actor);

		if (SelectedCharacter->SetToSelectedPlayer())
		{
		UE_LOG(LogTemp, Display, TEXT("Actor was selected"));
		}
		else
		{
		SelectedCharacter = nullptr;
		UE_LOG(LogTemp, Display, TEXT("Actor cannot be selected"));
		}
		}
		}*/


		//}
	}
}


void ANorthernCampPlayerController::DoubleTapTouchCondition()
{
	// Here I check for double tap events by looking if the finger either: moved to much, pressed to long, waited to long to press again.
	if(FingerTouched)
	{
		FingerTapAmount = FingerTapAmount + 1;
		FingerTouched = false;
	}
	//Reset if the duration of the tap was to long, and if the last time tapped was to long. Or if the player move the screen fast.
	if(FingerTapAmount != 0 && (FingerTouchDuration > 13.0f || Time > (LastTimeFingerTouched + 13.0f) || ((PreviousTouchLocation.X - StartingLocationFingerX > 10.0f) || (PreviousTouchLocation.Y - StartingLocationFingerY > 10.0f))))
	{
		FingerTapAmount = 0;
	}
	if(FingerTapAmount == 2)
	{
		FingerTapAmount = 0;
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(SelectedHero->GetController(), LastTouchHitResults.Location);
	}
}

void ANorthernCampPlayerController::MoveCameraAccordingToFinger()
{
	if (MyOwner)
	{
		FVector CurrentLocation = MyOwner->GetActorLocation();
		float FloatToAddOnY = (PreviousTouchLocation.X - NewTouchLocation.X) * 2.0f;
		float FloatToAddOnX = (PreviousTouchLocation.Y - NewTouchLocation.Y) * 2.0f;

		if (PreviousTouchLocation.X == 0.0f)
		{
			FloatToAddOnY = 0.0f;
		}
		if (PreviousTouchLocation.Y == 0.0f)
		{
			FloatToAddOnX = 0.0f;
		}
		FVector NewLocation = MyOwner->GetActorLocation();
		//Up and Down swipe is X
		FloatToAddOnX = -1 * FloatToAddOnX;
		NewLocation.X = CurrentLocation.X + FloatToAddOnX;
		//Left and right swipe is Y
		NewLocation.Y = CurrentLocation.Y + FloatToAddOnY;

		MyOwner->SetActorLocation(NewLocation);
			
		//Look at how much the difference was to make a sort of speed when the finger is released
		PreviousTouchLocation = NewTouchLocation;
	}
}

void ANorthernCampPlayerController::KeepCameraInHeroBounds(float DeltaTime)
{
	//Get distance, set the the position to go to. 
	FVector CurrentLocation = MyOwner->GetActorLocation();
	FVector HeroLocationXY = FVector(SelectedHero->GetActorLocation().X, SelectedHero->GetActorLocation().Y, MyOwner->GetActorLocation().Z);

	float DistanceFromCharacter = FVector(HeroLocationXY - CurrentLocation).Size();

	if(DistanceFromCharacter > 2000.0f)
	{
		MyOwner->SetActorLocation(FMath::Lerp(CurrentLocation, HeroLocationXY, (DeltaTime * 1)));
		bCameraIsMoving = true;
		PreviousTouchLocation.X = 0.0f;
		PreviousTouchLocation.Y = 0.0f;
	}
	else
	{
		bCameraIsMoving = false;
	}
	
}



