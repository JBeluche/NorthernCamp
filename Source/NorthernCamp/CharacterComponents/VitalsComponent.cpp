// Copyright Creating Mountains!


#include "NorthernCamp/CharacterComponents/VitalsComponent.h"

#include "EngineUtils.h"
#include "GameFramework/Character.h"
#include "NorthernCamp/AIController/AISettlerController.h"
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

	CurrentWaterMeter = 0.0f;
	CurrentFoodMeter = 100.0f;
	CurrentSleepMeter = 100.0f;
	CurrentFunFireMeter = 100.0f;
	WaterIsLowThreshold = 10.0f;
	
	Owner = Cast<ACharacter>(GetOwner());
	Settler = Cast<ACharacterSettler>(GetOwner());
	Controller = Cast<AAISettlerController>(Owner->GetController());

	for (TActorIterator<ADayNightActorController> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		DayNightController = *ActorItr;
	}

	UpdateVitals();
	//UE_LOG(LogTemp, Error, TEXT("VitalsComponent: begin play Settler: %s"), *GetReadableName());

	GetWorld()->GetTimerManager().SetTimer(UpdateVitalsTHandler, this, &UVitalsComponent::UpdateVitals, TimeIntervalVitalsCheck, true);

	
}

void UVitalsComponent::UpdateVitals()
{
	if(Controller == nullptr){UE_LOG(LogTemp, Error, TEXT("VitalsComponent: I dont have a controller? te fuck? Settler: %s"), *GetReadableName());	return;	}

	if(DayNightController)
	{

		//////
		// WATER
		//UE_LOG(LogTemp, Error, TEXT("VitalsComponent: Current water: %f"), CurrentWaterMeter);

		if(CurrentWaterMeter <= WaterIsLowThreshold)
        {
			NeedWater = true;
			//RequestResourceNeed(EResourceRequest::Thirsty);
        }
		else
		{
			NeedWater = false;
		}
        			
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
		if(CurrentWaterMeter < WaterIsLowThreshold)
		{
			NeedFood = true;
		}
		else
		{
			NeedFood = false;
		}
        		
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
/*
void UVitalsComponent::RequestResourceNeed(EResourceRequest Request)
{

	if(!RequestsMadeResourceNeed.Contains(Request))
	{
		UE_LOG(LogTemp, Error, TEXT("VitalsComponent: Adding a request"));


		if(Request == EResourceRequest::Thirsty)
		{
			RequestsMadeResourceNeed.Add(Request);

			FResourceInfo ResourceNeed;
			ResourceNeed.PriorityNumber = 100;
			ResourceNeed.ResourceType = EResourceType::Water;
			ResourceNeed.Amount = 1;
			Settler->ResourceManagerComp->AddResourceNeed(ResourceNeed);
		}
		
	}
}

void UVitalsComponent::RequestExecuted(EResourceRequest Request)
{
	if(RequestsMadeResourceNeed.Contains(Request))
	{
		RequestsMadeResourceNeed.Remove(Request);

		if(Request == EResourceRequest::Thirsty)
		{
			//	CurrentWaterMeter = 100.0f;
		}
	}
	else{UE_LOG(LogTemp, Error, TEXT("Vitals component: You tried to RequestExecute, but the requestsmaderesourceneed array does not find you request.")); return;}
}
*/

float UVitalsComponent::GetVitalLevel(EVital Vital)
{
	if(Vital == EVital::Water)
	{
		return CurrentWaterMeter;
	}

	return 0.0f;
}
