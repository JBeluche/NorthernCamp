// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NorthernCamp/Controllers/DayNightActorController.h"

#include "VitalsComponent.generated.h"


class AAISettlerController;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NORTHERNCAMP_API UVitalsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVitalsComponent();

	//////
	// SETTINGS

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	float TimeIntervalVitalsCheck;

	//////
	// HEALTH

	float HealthMeter;
	
	//////
	// WATER

	float CurrentWaterMeter;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	float WaterPercentageDecreasePerHour;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Water Meter")
	float WaterIsLowThreshold;

	bool NeedWater;
	bool NeedFood;
	

	//////
	// FOOD

	float CurrentFoodMeter;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	float FoodPercentageDecreasePerHour;

	//////
	// SLEEP

	float CurrentSleepMeter;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	float SleepPercentageDecreasePerHour;

	//////
	// FUN FIRE

	float CurrentFunFireMeter;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	float FunFirePercentageDecreasePerHour;

	


	float FunLoveMeter;
	float FunBookMeter;
	float FunMusicMeter;
	float FunBeerMeter;
	float FunReligionMeter;
	float InitialWaterMeter;

	
	FTimerHandle UpdateVitalsTHandler;

	void UpdateVitals();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	ADayNightActorController* DayNightController;
	
	ACharacter* Owner;
	AAISettlerController* Controller;

		
};
