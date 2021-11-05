// Copyright Creating Mountains!


#include "NorthernCamp/CharacterComponents/CharacterVitalsComponent.h"

// Sets default values for this component's properties
UCharacterVitalsComponent::UCharacterVitalsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	InitialWaterMeter = 100.0f;

	// ...
}


// Called when the game starts
void UCharacterVitalsComponent::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(UpdateVitalsTHandler, this, &UCharacterVitalsComponent::UpdateVitals, 2.0f, true);

	//InitialHealthMeter = 100.0f;

	/*InitialFoodMeter = 100.0f;
	InitialSleepMeter = 100.0f;
	InitialFunFireMeter = 100.0f;*/
	

	
}

void UCharacterVitalsComponent::UpdateVitals()
{



	//Water vitals
	CurrentWaterMeter = InitialWaterMeter - (CurrentWaterMeter - WaterDecreaseSpeed);
	

	//Food vitals
	FoodMeter = FoodMeter - FoodDecreaseSpeed;


	//Sleep vitals
	SleepMeter = SleepMeter - SleepDecreaseSpeed;

	FunFireMeter = FunFireMeter - FunFireDecreaseSpeed;
	/*FunLoveMeter;
	FunBookMeter;
	FunMusicMeter;
	FunBeerMeter;
	FunReligionMeter;*/
}

float UCharacterVitalsComponent::GetHealthMeter()
{
	return HealthMeter;
}

float UCharacterVitalsComponent::GetWaterMeter()
{
	UE_LOG(LogTemp, Error, TEXT("Component Water is: %f"), CurrentWaterMeter);

	return CurrentWaterMeter;
}

float UCharacterVitalsComponent::GetFoodMeter()
{
	return FoodMeter;
}

float UCharacterVitalsComponent::GetSleepMeter()
{
	return SleepMeter;
}

float UCharacterVitalsComponent::GetFunFireMeter()
{
	return FunFireMeter;
}

