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
#include "EngineUtils.h"

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

	CampPawn = nullptr;
	MainPlayerPawn = nullptr;
	SelectedCharacter = nullptr;
}

void ANorthernCampPlayerController::BeginPlay()
{
	//Seting playable pawns.
	for (TActorIterator<ACampPawn> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		CampPawn = *ActorItr;
	}
	for (TActorIterator<AMainPlayerPawn> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		MainPlayerPawn = *ActorItr;
	}

	CurrentPawnEnum = ECurrentPawn::ArenCharacter;
	SetOwner();
	FingerTouchDuration = 0.0f;
	LastFingerTouchDuration = 0.0f;
}

void ANorthernCampPlayerController::PlayerTick(float DeltaTime)
{

	Super::PlayerTick(DeltaTime);

	//Player controls
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
	else if (CurrentPawnEnum == ECurrentPawn::ARENCHARACTER)
	{*/

		GetInputTouchState(ETouchIndex::Touch1, NewTouchLocation.X, NewTouchLocation.Y, bIsFingerTouching);
		if (bIsFingerTouching)
		{

			FingerTouchDuration = (FingerTouchDuration + 1.0f);

			GetHitResultUnderFinger(
				ETouchIndex::Touch1,
				ECC_Pawn,
				true,
				LastTouchHitResults);

			//If this is the case, do a cast?
			if (MyOwner)
			{
				FVector CurrentLocation = MyOwner->GetActorLocation();
				float FloatToAddOnY = (PreviousTouchLocation.X - NewTouchLocation.X) * 5.0f;
				float FloatToAddOnX = (PreviousTouchLocation.Y - NewTouchLocation.Y) * 5.0f;

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
	/*	else
		{
			LastFingerTouchDuration = FingerTouchDuration;
			FingerTouchDuration = 0.0f;

			if (LastFingerTouchDuration < 50.0f && LastFingerTouchDuration > 2.0f)
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
			}

			PreviousTouchLocation.X = 0.0f;
			PreviousTouchLocation.Y = 0.0f;
		}
	}*/

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

void ANorthernCampPlayerController::SetOwner()
{
	MyOwner = Cast<AActor>(GetPawn());
}
/*
UUserWidget* ANorthernCampPlayerController::GetDialogWidget()
{
	return CreateWidget<UUserWidget>(this, DialogWidget, FName("Dialog Controls"));
}*/



