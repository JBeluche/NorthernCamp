// Copyright Creating Mountains!


#include "NorthernCamp/CharacterComponents/VitalsComponent.h"

#include "EngineUtils.h"
#include "NorthernCamp/Controllers/DayNightActorController.h"

// Sets default values for this component's properties
UVitalsComponent::UVitalsComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	WaterPercentageDecreasePerHour = 7.5f;
	FoodPercentageDecreasePerHour = 3.75f;
	SleepPercentageDecreasePerHour = 2.4f;
	FunFirePercentageDecreasePerHour = 10.0f;

	TimeIntervalVitalsCheck = 2.0f;

	
}


// Called when the game starts
void UVitalsComponent::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(UpdateVitalsTHandler, this, &UVitalsComponent::UpdateVitals, TimeIntervalVitalsCheck, true);

	CurrentWaterMeter = 100.0f;
	CurrentFoodMeter = 100.0f;
	CurrentSleepMeter = 100.0f;
	CurrentFunFireMeter = 100.0f;

	for (TActorIterator<ADayNightActorController> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		DayNightController = *ActorItr;
	}
	
}

void UVitalsComponent::UpdateVitals()
{
	//Get the rate
	//Get how much time should elapse with the rate
	//Subtract by looking at WaterPercentageDecreasePerHour

	if(DayNightController)
	{

		//////
		// WATER
		//////
		if(CurrentWaterMeter <= 0.0f)
		{
			//You are dying 
			CurrentWaterMeter = 0.0f;
		}
		else
		{
			float WaterToSubtract =	(TimeIntervalVitalsCheck * WaterPercentageDecreasePerHour) / DayNightController->SecondsPerHour;
			CurrentWaterMeter =  CurrentWaterMeter - WaterToSubtract;

		}
	
		//////
		// FOOD
		//////
		if(CurrentFoodMeter <= 0.0f)
		{
			//You are dying 
			CurrentFoodMeter = 0.0f;
		}
		else
		{
			float FoodToSubtract =	(TimeIntervalVitalsCheck * FoodPercentageDecreasePerHour) / DayNightController->SecondsPerHour;
			CurrentFoodMeter =  CurrentFoodMeter - FoodToSubtract;

		}

		//////
		// SLEEP
		//////
		if(CurrentSleepMeter <= 0.0f)
		{
			//You are dying 
			CurrentSleepMeter = 0.0f;
		}
		else
		{
			float SleepToSubtract =	(TimeIntervalVitalsCheck * SleepPercentageDecreasePerHour) / DayNightController->SecondsPerHour;
			CurrentSleepMeter =  CurrentSleepMeter - SleepToSubtract;

		}

		
		//////
		// FUN FIRE
		//////
		if(CurrentFunFireMeter <= 0.0f)
		{
			//You are dying 
			CurrentFunFireMeter = 0.0f;
		}
		else
		{
			float FunFireToSubtract =	(TimeIntervalVitalsCheck * FunFirePercentageDecreasePerHour) / DayNightController->SecondsPerHour;
			CurrentFunFireMeter =  CurrentFunFireMeter - FunFireToSubtract;

		}
		
	}
	else
	{
		return;
	}
	
	

}
