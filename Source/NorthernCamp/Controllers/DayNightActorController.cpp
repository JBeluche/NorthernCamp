// Copyright Creating Mountains!


#include "NorthernCamp/Controllers/DayNightActorController.h"

#include "Components/LightComponent.h"
#include "Engine/DirectionalLight.h"


// Sets default values
ADayNightActorController::ADayNightActorController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ADayNightActorController::BeginPlay()
{
	Super::BeginPlay();

	CurrentDay = 1;

	//Start the time timer
	SetTimeTo(StartingHour, 0.0f);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ADayNightActorController::MoveTime, TimeUpdatesInterval, true);

	TotalDayLightTimeInVirtualMinutes = (SunsetHour - SunriseHour) * 60;
	DayAngleToAddOnZ = (SunSettingPosition - SunRisingPosition) / ((SecondsPerHour / TimeUpdatesInterval) * (SunsetHour - SunriseHour));
	DayAngleToAddOnY = ((SunPositionHighestPoint - SunPositionLowestPoint) / ((SecondsPerHour / TimeUpdatesInterval) * (SunsetHour - SunriseHour)) * 2);

	NightAngleToAddOnZ = (MoonEndLocation - MoonStartLocation) / ((SecondsPerHour / TimeUpdatesInterval) * ((24.0f - SunsetHour) + SunriseHour));

	//Moonset - Moonrise
	LuminositiToAddBetweenNightAndGoldenHour = MoonLumosity / ((SecondsPerHour / TimeUpdatesInterval) * ((1 * MoonSetDuration) / 60));
	LuminositiToAddBetweenGoldenHourAndNight = MoonLumosity / ((SecondsPerHour / TimeUpdatesInterval) * ((1 * MoonRiseDuration) / 60));

	//Sunrise
	TemperatureToAddBetweenGoldenHourAndDay = (TemperatureDay - TemperatureGoldenhours) / ((SecondsPerHour / TimeUpdatesInterval) * ((1 * SunriseDuration) / 60));
	LuminositiToAddBetweenGoldenHourAndDay = SunLumosity / ((SecondsPerHour / TimeUpdatesInterval) * ((1 * SunriseDuration) / 60));

	//Sunset
	TemperatureToAddBetweenDayAndGoldenHour = (TemperatureDay - TemperatureGoldenhours) / ((SecondsPerHour / TimeUpdatesInterval) * ((1 * SunsetDuration) / 60));
	LuminositiToAddBetweenDayAndGoldenHour = SunLumosity / ((SecondsPerHour / TimeUpdatesInterval) * ((1 * SunsetDuration) / 60));



	SunAndMoonLightComponent = Cast<ULightComponent>(SunLigth->GetLightComponent());

	SunriseStartInMinutes = SunriseHour * 60;
	SunriseMidwayInMinutes = SunriseHour * 60 + (SunriseDuration / 2);
	SunriseEndInMinutes = SunriseHour * 60 + SunriseDuration;
	
	SunpeakInMinutes = (SunriseHour * 60) + TotalDayLightTimeInVirtualMinutes / 2;
	
	SunsetStartInMinutes = (SunriseHour * 60) + TotalDayLightTimeInVirtualMinutes - SunsetDuration;
	SunsetMidwayInMinutes = (SunriseHour * 60) + TotalDayLightTimeInVirtualMinutes - (SunsetDuration / 2);
	SunsetEndInMinutes = (SunriseHour * 60) + TotalDayLightTimeInVirtualMinutes;

	MoonSetStartInMinutes = SunriseStartInMinutes - MoonSetDuration;
	MoonRiseEndInMinutes = SunsetEndInMinutes + MoonRiseDuration;

}

void ADayNightActorController::SetTimeTo(float HourToSet, float MinuteToSet)
{
	CurrentTimeMinutes = MinuteToSet;
	CurrentTimeHours = HourToSet;
}

void ADayNightActorController::MoveTime()
{
	//////
	// Advances the time
	//////
	
	//Check time speed and move time according to the calculation
	CurrentTimeMinutes = CurrentTimeMinutes + (60.0f / (SecondsPerHour / TimeUpdatesInterval));
	
	if(CurrentTimeMinutes >= 60.0f)
	{
		CurrentTimeHours++;
		AnHourStruck.Broadcast(CurrentTimeHours);
		if(CurrentTimeHours >= 24.0f){CurrentDay++; ADayEnded.Broadcast(CurrentDay); CurrentTimeHours = 0.0f;}
		//if(CurrentTimeMinutes > 60.0f){CurrentTimeMinutes = 60.0f / (SecondsPerHour / TimeUpdatesInterval);}
		if(CurrentTimeMinutes >= 60.0f){CurrentTimeMinutes = CurrentTimeMinutes - 60.0f; }
	}

	//Get time frames to use.
	CurrentTimeInMinutes = (CurrentTimeHours * 60) + CurrentTimeMinutes; 
	
	CurrentMinutesSinceSunriseStart = CurrentTimeInMinutes - SunriseStartInMinutes;
	CurrentMinutesSinceSunriseMidway = CurrentTimeInMinutes - SunriseMidwayInMinutes;
	CurrentMinutesSinceSunriseEnd = CurrentTimeInMinutes - SunriseEndInMinutes;
	
	CurrentMinutesSinceSunPeak = CurrentTimeInMinutes - SunpeakInMinutes;
	
	CurrentMinutesSinceSunsetStart = CurrentTimeInMinutes - SunsetStartInMinutes;
	CurrentMinutesSinceSunsetMidway = CurrentTimeInMinutes - SunsetMidwayInMinutes;
	CurrentMinutesSinceSunsetEnd = CurrentTimeInMinutes - SunsetEndInMinutes;

	CurrentMinutesSinceMoonSetStart= CurrentTimeInMinutes - MoonSetStartInMinutes;
	CurrentMinutesSinceMoonRiseEnd = CurrentTimeInMinutes - MoonRiseEndInMinutes;

	//////
	// The following code handles the sunlight(directional light), aka moon, location in the sky
	//////
	
	//Its morning
	if (SunriseStartInMinutes <= CurrentTimeInMinutes && CurrentTimeInMinutes <= SunpeakInMinutes)
	{
		SunLocationZ = SunRisingPosition + (DayAngleToAddOnZ * (((CurrentMinutesSinceSunriseStart * SecondsPerHour) / 60) / TimeUpdatesInterval));
		SunLocationY = SunPositionLowestPoint + (DayAngleToAddOnY * (((CurrentMinutesSinceSunriseStart * SecondsPerHour) / 60) / TimeUpdatesInterval));

	}
	//Its midday
	else if (SunpeakInMinutes <= CurrentTimeInMinutes && CurrentTimeInMinutes <= SunsetEndInMinutes)
	{
		SunLocationZ = SunRisingPosition + (DayAngleToAddOnZ * (((CurrentMinutesSinceSunriseStart * SecondsPerHour) / 60) / TimeUpdatesInterval));
		SunLocationY = SunPositionHighestPoint - (DayAngleToAddOnY * (((CurrentMinutesSinceSunPeak * SecondsPerHour) / 60) / TimeUpdatesInterval));
	}
	//Its night
	else
	{
		SunLocationZ = MoonStartLocation + (NightAngleToAddOnZ * (((CurrentMinutesSinceSunsetEnd * SecondsPerHour) / 60) / TimeUpdatesInterval));
		SunLocationY = SunPositionHighestPoint;
	}

	if(SunLigth)
	{
		SunLigth->SetActorRelativeRotation(FRotator(SunLocationY, SunLocationZ, 0.0f));
	}

	//////
	// The following code handles color and light,
	//////

	//Set day temperatures(Ignore the sun set and sunrise)
	if (SunriseEndInMinutes <= CurrentTimeInMinutes && CurrentTimeInMinutes <= SunsetStartInMinutes)
	{
		SunAndMoonLightComponent->SetTemperature(TemperatureDay);
		SunAndMoonLightComponent->SetIntensity(SunLumosity);
		SunColor.R = 1.0f;
		SunColor.G = 1.0f;
		SunColor.B = 1.0f;
		SunColor.A = 1.0f;
		SunLigth->SetLightColor(SunColor);
	}
	//Set night temperatures(Ignore the moon set and moon rise)
	else if(MoonRiseEndInMinutes <= CurrentTimeInMinutes || CurrentTimeInMinutes <= MoonSetStartInMinutes)
	{
		SunAndMoonLightComponent->SetTemperature(TemperatureNight);
		SunAndMoonLightComponent->SetIntensity(MoonLumosity);
		SunColor.R = .5f;
		SunColor.G = .5f;
		SunColor.B = 1.0f;
		SunColor.A = 1.0f;
		SunLigth->SetLightColor(SunColor);
	}
	//Moonsetting
	else if(MoonSetStartInMinutes <= CurrentTimeInMinutes && CurrentTimeInMinutes <= SunriseStartInMinutes)
	{
		float NewIntensity = MoonLumosity - (LuminositiToAddBetweenNightAndGoldenHour * (((CurrentMinutesSinceMoonSetStart * SecondsPerHour) / 60) / TimeUpdatesInterval));
		SunAndMoonLightComponent->SetIntensity(NewIntensity); 	
		SunAndMoonLightComponent->SetTemperature(TemperatureNight);
		SunColor.R = .5f;
		SunColor.G = .5f;
		SunColor.B = 1.0f;
		SunColor.A = 1.0f;
		SunLigth->SetLightColor(SunColor);

	}
	//Sunrise part 1
	else if(SunriseStartInMinutes <= CurrentTimeInMinutes && CurrentTimeInMinutes <= SunriseMidwayInMinutes)
	{
		SunAndMoonLightComponent->SetTemperature(TemperatureGoldenhours);
		SunColor.R = 1.0f;
		SunColor.G = 1.0f;
		SunColor.B = 1.0f;
		SunColor.A = 1.0f;
		SunLigth->SetLightColor(SunColor);
		float NewIntensity = 0.0f + (LuminositiToAddBetweenGoldenHourAndDay * (((CurrentMinutesSinceSunriseStart * SecondsPerHour) / 60) / TimeUpdatesInterval) * 2);
		SunAndMoonLightComponent->SetIntensity(NewIntensity); 
	}
	//Sunrise part 2
	else if(SunriseMidwayInMinutes <= CurrentTimeInMinutes && CurrentTimeInMinutes <= SunriseEndInMinutes)
	{
		SunAndMoonLightComponent->SetIntensity(SunLumosity);
		SunColor.R = 1.0f;
		SunColor.G = 1.0f;
		SunColor.B = 1.0f;
		SunColor.A = 1.0f;
		SunLigth->SetLightColor(SunColor);
		float NewTemperature = TemperatureGoldenhours + (TemperatureToAddBetweenGoldenHourAndDay * (((CurrentMinutesSinceSunriseMidway * SecondsPerHour) / 60) / TimeUpdatesInterval) * 2);
		SunAndMoonLightComponent->SetTemperature(NewTemperature);
	}
	//Sunset part 1
	else if(SunsetStartInMinutes <= CurrentTimeInMinutes && CurrentTimeInMinutes <= SunsetMidwayInMinutes)
	{
		SunAndMoonLightComponent->SetIntensity(SunLumosity);
		SunColor.R = 1.0f;
		SunColor.G = 1.0f;
		SunColor.B = 1.0f;
		SunColor.A = 1.0f;
		SunLigth->SetLightColor(SunColor);
		float NewTemperature = TemperatureDay - (TemperatureToAddBetweenDayAndGoldenHour * (((CurrentMinutesSinceSunsetStart * SecondsPerHour) / 60) / TimeUpdatesInterval) * 2);
		SunAndMoonLightComponent->SetTemperature(NewTemperature);
	}
	//Sunset part 2
	else if(SunsetMidwayInMinutes <= CurrentTimeInMinutes && CurrentTimeInMinutes <= SunsetEndInMinutes)
	{
		SunAndMoonLightComponent->SetTemperature(TemperatureGoldenhours);
		SunColor.R = 1.0f;
		SunColor.G = 1.0f;
		SunColor.B = 1.0f;
		SunColor.A = 1.0f;
		SunLigth->SetLightColor(SunColor);
		float NewIntensity = SunLumosity - (LuminositiToAddBetweenDayAndGoldenHour * (((CurrentMinutesSinceSunsetMidway * SecondsPerHour) / 60) / TimeUpdatesInterval) * 2);
		SunAndMoonLightComponent->SetIntensity(NewIntensity); 
	}
	//Moonrising
	else if(SunsetEndInMinutes <= CurrentTimeInMinutes && CurrentTimeInMinutes <= MoonRiseEndInMinutes)
	{
		SunColor.R = .5f;
		SunColor.G = .5f;
		SunColor.B = 1.0f;
		SunColor.A = 1.0f;
		SunLigth->SetLightColor(SunColor);
		float NewIntensity = 0.0f + (LuminositiToAddBetweenGoldenHourAndNight * (((CurrentMinutesSinceSunsetEnd * SecondsPerHour) / 60) / TimeUpdatesInterval));
		SunAndMoonLightComponent->SetIntensity(NewIntensity); 	
		SunAndMoonLightComponent->SetTemperature(TemperatureNight);
	}
}

//		UE_LOG(LogTemp, Error, TEXT("Moonrising, Time: %f:%f | Temp(%f) | Lumos(%f)"), CurrentTimeHours, CurrentTimeMinutes, SunAndMoonLightComponent->Temperature, SunLigth->GetBrightness());



