// Copyright Epic Games, Inc. All Rights Reserved.

#include "NorthernCampPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "NorthernCamp/UserWidgets/SettlerInfoUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "NorthernCamp/Pawns/LooseCameraPawn.h"
#include "NorthernCamp/Pawns/CampCameraPawn.h"
#include "NorthernCamp/Characters/CharacterHero.h"
#include "NorthernCamp/Characters/CharacterSettler.h"
#include "Math/UnrealMathUtility.h"
#include "Components/ScrollBox.h"
 	

#include "Engine/World.h"
#include "EngineUtils.h"
#include "NavigationSystem.h"


///////
//	
///////

ANorthernCampPlayerController::ANorthernCampPlayerController()
{
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;

	const ConstructorHelpers::FClassFinder<UUserWidget> WBPControlsLooseCamera(TEXT("/Game/Blueprints/UserWidgets/WBP_LooseCameraMain"));
	const ConstructorHelpers::FClassFinder<UUserWidget> WBPSettlersInfoUserWidget(TEXT("/Game/Blueprints/UserWidgets/WBP_SettlerInfo"));
	ConstructorHelpers::FClassFinder<UUserWidget> WBPControlsCamp(TEXT("/Game/Blueprints/UserWidgets/WBP_CampCameraControls"));
	//ConstructorHelpers::FClassFinder<UUserWidget> DialogWidgetClass(TEXT("/Game/Blueprints/Widgets/WBP_Dialog"));

	
	
	LooseCameraUserWidget = WBPControlsLooseCamera.Class;
	SettlerInfoUserWidget = WBPSettlersInfoUserWidget.Class;
	CampControlClass = WBPControlsCamp.Class;
	//DialogWidget = DialogWidgetClass.Class;

	CampCameraPawn = nullptr;
	LooseCameraPawn = nullptr;
	SelectedHero = nullptr;
	SelectedSettler = nullptr;

	
}

void ANorthernCampPlayerController::BeginPlay()
{

	SwitchPawn(ECurrentPawn::LooseCamera);
	SetSelectedHero(EHero::Will);

	FingerTouchDuration = 0.0f;
	
	//Command to make the shadows appear for longer distances.
	GEngine->Exec( GetWorld(), TEXT( "r.Shadow.RadiusThreshold 0.01" ) );
	GEngine->Exec( GetWorld(), TEXT( "stat fps" ) );
}

void ANorthernCampPlayerController::PlayerTick(float DeltaTime)
{

	Super::PlayerTick(DeltaTime);

	//Easy way to measure amount of ticks.
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
			UpdateUI(ECurrentUI::LooseCamera);
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
			UpdateUI(ECurrentUI::Camp);
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
		SelectSettlerCondition();
		DoubleTapTouchCondition();
		//Resetting everything to check again
		PreviousTouchLocation.X = 0.0f;
		PreviousTouchLocation.Y = 0.0f;
		FingerTouchDuration = 0.0f;


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
			UpdateUI(ECurrentUI::SettlerInfo);
		}
	}
}

void ANorthernCampPlayerController::UpdateUI(ECurrentUI NewCurrentUI)
{
	if(Controls){Controls->RemoveFromViewport();}
	bIsInMenu = false;
	CurrentScrollBar = nullptr;
	if(NewCurrentUI == ECurrentUI::SettlerInfo)
	{
		Controls = CreateWidget<UUserWidget>(this, SettlerInfoUserWidget, FName("Settler Information Widget"));
		CurrentScrollBar = Cast<UScrollBox>(Cast<USettlerInfoUserWidget>(Controls)->ScrollboxWholeWindow);
		bIsInMenu = true;
	}
	else if(NewCurrentUI == ECurrentUI::LooseCamera)
	{
		Controls = CreateWidget<UUserWidget>(this, LooseCameraUserWidget, FName("Main Loose Camera Controls"));
	}
	else if(NewCurrentUI == ECurrentUI::Camp)
	{
		Controls = CreateWidget<UUserWidget>(this, CampControlClass, FName("Camp Controls"));
	}
	
	Controls->AddToViewport();
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
			if(SelectedHero != nullptr)
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(SelectedHero->GetController(), LastTouchHitResults.Location);
			}
		}
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

		//Check if you need to move the actor or the screen scroll.
		if(bIsInMenu)
		{
			CurrentScrollBar->SetScrollOffset(FloatToAddOnY);
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
		PreviousTouchLocation.X = 0.0f;
		PreviousTouchLocation.Y = 0.0f;
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




