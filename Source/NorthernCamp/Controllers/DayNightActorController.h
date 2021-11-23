// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DayNightActorController.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnHourStruck, float, CurrentHour);


class ADirectionalLight;


UCLASS()
class NORTHERNCAMP_API ADayNightActorController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADayNightActorController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(BlueprintAssignable, Category="Hourly events")
	FOnAnHourStruck AnHourStruck;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ADirectionalLight* SunLigth;

	FTimerHandle TimerHandle;
	ULightComponent* SunAndMoonLightComponent;

	float CurrentTimeMinutes;
	float CurrentTimeHours;

	float SunLocationZ;
	float TotalDayLightTimeInVirtualMinutes;
	
	float DayAngleToAddOnZ;
	float DayAngleToAddOnY;

	float TemperatureToAddBetweenNightAndGoldenHour;
	float TemperatureToAddBetweenGoldenHourAndDay;
	
	float TemperatureToAddBetweenDayAndGoldenHour;
	float TemperatureToAddBetweenGoldenHourAndNight;

	float LuminositiToAddBetweenNightAndGoldenHour;
	float LuminositiToAddBetweenGoldenHourAndNight;
	float LuminositiToAddBetweenDayAndGoldenHour;
	float LuminositiToAddBetweenGoldenHourAndDay;
	
	float NightAngleToAddOnZ;
	float NightAngleToAddOnY;

	FLinearColor SunColor;
	
	float SunLocationY;


	//Helpers
	//Get the current time and check if the sun is going up or down.
	float CurrentTimeInMinutes;
	
	float SunriseStartInMinutes;
	float SunriseMidwayInMinutes;
	float SunriseEndInMinutes;
	
	float SunpeakInMinutes;
	
	float SunsetStartInMinutes;
	float SunsetMidwayInMinutes;
	float SunsetEndInMinutes;

	float MoonSetStartInMinutes;
	float MoonRiseEndInMinutes;

	//When everything started or ended.
	float CurrentMinutesSinceSunriseStart;
	float CurrentMinutesSinceSunriseMidway;
	float CurrentMinutesSinceSunriseEnd;
	
	float CurrentMinutesSinceSunPeak;
	
	float CurrentMinutesSinceSunsetStart;
	float CurrentMinutesSinceSunsetMidway;
	float CurrentMinutesSinceSunsetEnd;

	float CurrentMinutesSinceMoonSetStart;
	float CurrentMinutesSinceMoonRiseEnd;


	//Locations
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locations")
	float SunPositionHighestPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locations")
	float SunPositionLowestPoint;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locations")
	float MoonStartLocation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locations")
	float MoonEndLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locations")
	float SunRisingPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locations")
	float SunSettingPosition;

	
	//Light Options
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light options")
	float SunLumosity;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light options")
    float MoonLumosity;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light options")
	float TemperatureNight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light options")
	float TemperatureDay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light options")
	float TemperatureGoldenhours;

	//Time options
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time options")
	float SunriseHour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time options")
	float SunsetHour;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time options")
	float SecondsPerHour;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time options")
	float StartingHour;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time options")
	float TimeUpdatesInterval;

	//Durations
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Durations")
	float SunriseDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Durations")
	float SunsetDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Durations")
	float MoonRiseDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Durations")
	float MoonSetDuration;
	

	void SetTimeTo(float HourToSet, float MinuteToSet);

	void MoveTime();
	
};
