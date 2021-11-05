// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterVitalsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NORTHERNCAMP_API UCharacterVitalsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterVitalsComponent();

	//Water meter
	float HealthMeter;

	float GetHealthMeter();

	
	//Water meter
	float CurrentWaterMeter;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Water Meter")
	float WaterDecreaseSpeed;

	float GetWaterMeter();

	//Food meter
	float FoodMeter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Water Meter")
	float FoodDecreaseSpeed;

	float GetFoodMeter();

	
	//Sleep meter	
	float SleepMeter;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Water Meter")
	float SleepDecreaseSpeed;

	float GetSleepMeter();

	//Fun meters
	float FunFireMeter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Water Meter")
	float FunFireDecreaseSpeed;

	float GetFunFireMeter();

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






		
};
