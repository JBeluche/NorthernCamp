// Copyright Epic Games, Inc. All Rights Reserved.

#include "NorthernCampPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"

#include "Blueprint/UserWidget.h"
#include "NorthernCamp/Pawns/LooseCameraPawn.h"
#include "NorthernCamp/Pawns/CampCameraPawn.h"
#include "NorthernCamp/Characters/CharacterHero.h"
#include "NorthernCamp/Characters/CharacterSettler.h"
#include "Math/UnrealMathUtility.h"


#include "EngineUtils.h"
#include "NavigationSystem.h"

ANorthernCampPlayerController::ANorthernCampPlayerController()
{
		bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	CampCameraPawn = nullptr;
	LooseCameraPawn = nullptr;
	SelectedHero = nullptr;
	SelectedSettler = nullptr;
	UIController = CreateDefaultSubobject<UUIController>(TEXT("UI Controller"));
}

void ANorthernCampPlayerController::BeginPlay()
{
	for (TActorIterator<AResourceController> ActorItr(GetWorld()); ActorItr; ++ActorItr) 
	{ 
		ResourceController = Cast<AResourceController>(*ActorItr); 
	}

	//Development settup basics
	SwitchPawn(ECurrentPawn::LooseCamera);
	SetSelectedHero(EHero::Will);

	//Setup basic stuff
	GEngine->Exec( GetWorld(), TEXT( "r.Shadow.RadiusThreshold 0.01" ) );


}

void ANorthernCampPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	//Easy way to measure amount of ticks. Should use a timer to measure how long the touch is pressed?
	Time = Time + 1.0f;

	if(CurrentPawnEnum == ECurrentPawn::LooseCamera){KeepCameraInHeroBounds(DeltaTime);}
	
	if(!bCameraIsMoving)
	{
		GetInputTouchState(ETouchIndex::Touch1, NewTouchLocation.X, NewTouchLocation.Y, bIsFingerTouching);
		FingerTouchHandler(DeltaTime);
	}
}

void ANorthernCampPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void ANorthernCampPlayerController::SwitchPawn(ECurrentPawn NewPawn)
{
	CurrentPawnEnum = NewPawn;

	if(LooseCameraPawn != nullptr || CampCameraPawn != nullptr)
	{
		UnPossess();
	}

	if (CurrentPawnEnum == ECurrentPawn::LooseCamera)
	{
		for (TActorIterator<ALooseCameraPawn> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			LooseCameraPawn = *ActorItr;
		}
		if(LooseCameraPawn != nullptr)
		{
			Possess(LooseCameraPawn);
			UIController->UpdateUI(ECurrentUI::LooseCamera);
			SetNewOwner();	
		}
	}
	else if (CurrentPawnEnum == ECurrentPawn::Camp)
	{
		for (TActorIterator<ACampCameraPawn> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			CampCameraPawn = *ActorItr;
		}
		if(CampCameraPawn != nullptr)
		{
			Possess(CampCameraPawn);
			UIController->UpdateUI(ECurrentUI::Camp);
			SetNewOwner();
		}
	}
}

void ANorthernCampPlayerController::SetNewOwner()
{
	MyOwner = Cast<AActor>(GetPawn());
}

void ANorthernCampPlayerController::FingerTouchHandler(float DeltaTime)
{
	
	//What to do if the finger is touching the screen
	if (bIsFingerTouching)
	{

		//This is to check the initial starting points of the finger drag
		if(FingerTouched == false && !UIController->bIsInMenu)
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
		SelectSettlerCondition();
		DoubleTapTouchCondition();

		ResetControlls();
	}
}

void ANorthernCampPlayerController::SelectSettlerCondition()
{
	//If there is no war the only thing to do is display the information. 
	if (FingerTouchDuration < 50.0f && FingerTouchDuration > 2.0f && Cast<ACharacterSettler>(LastTouchHitResults.Actor))
	{
		if(CurrentPawnEnum == ECurrentPawn::LooseCamera)
		{
			SelectedSettler = Cast<ACharacterSettler>(LastTouchHitResults.Actor);
			UIController->UpdateUI(ECurrentUI::SettlerInfo);
		}
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
	//Check if it hit something interesting.
	if(FingerTapAmount == 1)
	{
		
	}
	if(FingerTapAmount == 2)
	{
	
		FingerTapAmount = 0;
		if(CurrentPawnEnum == ECurrentPawn::LooseCamera)
		{
			if(SelectedHero != nullptr && UIController->bIsInMenu == false)
			{
				if(SelectedHero->bIsWounded)
				{
					//Popup message that hero is down
				}
				else
				{
					UAIBlueprintHelperLibrary::SimpleMoveToLocation(SelectedHero->GetController(), LastTouchHitResults.Location);
				}
			}
		}
	}
}

void ANorthernCampPlayerController::MoveCameraAccordingToFinger()
{
	if (MyOwner)
	{
		//This is here to fix the slider bar b.u.g. Which triggers endless touch events with incorrect locations
		if(NewTouchLocation.X == BugLocationX && NewTouchLocation.Y == BugLocationY && bSliderBugActive)
		{
			return;
		}
		else if(bSliderBugActive)
		{
			bSliderBugActive = false;
			return;
		}


		FVector CurrentLocation = MyOwner->GetActorLocation();
		float FloatToAddOnY = (PreviousTouchLocation.X - NewTouchLocation.X) * 2.0f;
		float FloatToAddOnX = (PreviousTouchLocation.Y - NewTouchLocation.Y) * 2.0f;

		//UE_LOG(LogTemp, Error, TEXT("Previous location Y: %f, Z: %f"), PreviousTouchLocation.X, PreviousTouchLocation.Y);

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

		//Check if you need to move the actor or the screen scroll.
		if(UIController->bIsInMenu)
		{
			BugLocationX = PreviousTouchLocation.X;
			BugLocationY = PreviousTouchLocation.Y;
			bSliderBugActive = true;
			ResetControlls();
		}
		else if(CurrentPawnEnum == ECurrentPawn::LooseCamera)
		{

			MyOwner->SetActorLocation(NewLocation);
		}
		else if(CurrentPawnEnum == ECurrentPawn::Camp)
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
}

void ANorthernCampPlayerController::KeepCameraInHeroBounds(float DeltaTime)
{
	if(SelectedHero == nullptr){return;}
	if(MyOwner == nullptr){return;}
	//Get distance, set the the position to go to. 
	FVector CurrentLocation = MyOwner->GetActorLocation();
	FVector HeroLocationXY = FVector(SelectedHero->GetActorLocation().X, SelectedHero->GetActorLocation().Y, MyOwner->GetActorLocation().Z);

	float DistanceFromCharacter = FVector(HeroLocationXY - CurrentLocation).Size();

	if(DistanceFromCharacter > SelectedHero->MaxCameraDistance)
	{
		MyOwner->SetActorLocation(FMath::Lerp(CurrentLocation, HeroLocationXY, (DeltaTime * 1)));
		bCameraIsMoving = true;
		ResetControlls();
	}
	else
	{
		bCameraIsMoving = false;
	}
	
}


void ANorthernCampPlayerController::SetSelectedHero(EHero CharacterHeroEnum)
{
	for (TActorIterator<ACharacterHero> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ACharacterHero *HeroToCheck = Cast<ACharacterHero>(*ActorItr);
	
		if(HeroToCheck->HeroEnum == CharacterHeroEnum)
		{
			SelectedHero = *ActorItr;
	
			return;
		}
	}
}


void ANorthernCampPlayerController::ResetControlls()
{
	PreviousTouchLocation.X = 0.0f;
	PreviousTouchLocation.Y = 0.0f;
	FingerTouchDuration = 0.0f;
}





