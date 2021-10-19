// Copyright Creating Mountains!


#include "NorthernCamp/Controllers/DayNightActorController.h"
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

	//Start the time timer
	SetTimeTo(StartingHour, 0.0f);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ADayNightActorController::MoveTime, TimeUpdatesInterval, true);

	TotalDayLightTimeInVirtualMinutes = (SunsetHour - SunriseHour) * 60;
	AngleToAddOnZ = (SunSettingPosition - SunRisingPosition) / ((SecondsPerHour / TimeUpdatesInterval) * (SunsetHour - SunriseHour));
	AngleToAddOnY = ((SunPositionHighestPoint - SunPositionLowestPoint) / ((SecondsPerHour / TimeUpdatesInterval) * (SunsetHour - SunriseHour)) * 2);

	
}

void ADayNightActorController::SetTimeTo(float HourToSet, float MinuteToSet)
{
	CurrentTimeMinutes = MinuteToSet;
	CurrentTimeHours = HourToSet;
}

void ADayNightActorController::MoveTime()
{
	//Check time speed and move time according to the calculation
	CurrentTimeMinutes = CurrentTimeMinutes + (60.0f / (SecondsPerHour / TimeUpdatesInterval));

	if(CurrentTimeMinutes >= 60.0f)
	{
		CurrentTimeHours++;
		if(CurrentTimeHours >= 24.0f){CurrentTimeHours = 0.0f;}
		//if(CurrentTimeMinutes > 60.0f){CurrentTimeMinutes = 60.0f / (SecondsPerHour / TimeUpdatesInterval);}
		if(CurrentTimeMinutes >= 60.0f){CurrentTimeMinutes = CurrentTimeMinutes - 60.0f; }
	}
	UE_LOG(LogTemp, Warning, TEXT("Current Time: %f:%f"), FMath::RoundHalfToZero(CurrentTimeHours), FMath::RoundHalfToZero(CurrentTimeMinutes));

	
		//Get the current time and check if the sun is going up or down.
		float CurrentTimeInMinutes = (CurrentTimeHours * 60) + CurrentTimeMinutes; //380
		float MorningTimeStartInMinutes = SunriseHour * 60;
		float MiddayTimeStartInMinutes = (SunriseHour * 60) + TotalDayLightTimeInVirtualMinutes / 2;
		float DayTimeEndsInMinutes = (SunriseHour * 60) + TotalDayLightTimeInVirtualMinutes;
		float CurrentMinutesSinceSunrise = CurrentTimeInMinutes - MorningTimeStartInMinutes;
		float CurrentMinutesSinceMidday = CurrentTimeInMinutes - MiddayTimeStartInMinutes;

		//Its morning
		if (MorningTimeStartInMinutes <= CurrentTimeInMinutes && CurrentTimeInMinutes <= MiddayTimeStartInMinutes)
		{
			//Here I need to know how often the timer has ticked since sunrize to then multiply it by the angle to add.
			SunLocationZ = SunRisingPosition + (AngleToAddOnZ * (((CurrentMinutesSinceSunrise * SecondsPerHour) / 60) / TimeUpdatesInterval));
			SunLocationY = SunPositionLowestPoint + (AngleToAddOnY * (((CurrentMinutesSinceSunrise * SecondsPerHour) / 60) / TimeUpdatesInterval));

			UE_LOG(LogTemp, Error, TEXT("It's Morning! Y:%f Z: %f"), CurrentMinutesSinceSunrise, AngleToAddOnZ);
			bSunGoesDone = false;
		}
		//Its midday
		else if (MiddayTimeStartInMinutes <= CurrentTimeInMinutes && CurrentTimeInMinutes <= DayTimeEndsInMinutes)
		{
			SunLocationZ = SunRisingPosition + (AngleToAddOnZ * (((CurrentMinutesSinceSunrise * SecondsPerHour) / 60) / TimeUpdatesInterval));
			SunLocationY = SunPositionHighestPoint - (AngleToAddOnY * (((CurrentMinutesSinceMidday * SecondsPerHour) / 60) / TimeUpdatesInterval));

			UE_LOG(LogTemp, Error, TEXT("Its midday, Y:%f Z: %f SunPositionHighestPoint: %f, AngleToAddOnY: %f, CurrentMinutesSinceMidday: %f"), SunLocationY, SunLocationZ, SunPositionHighestPoint, AngleToAddOnY, CurrentMinutesSinceMidday);
			bSunGoesDone = true;
		}
		
		//Its Sunrise
		else if ((MorningTimeStartInMinutes - 60) <= CurrentTimeInMinutes && CurrentTimeInMinutes <= MorningTimeStartInMinutes)
		{
			UE_LOG(LogTemp, Error, TEXT("Its Sunrise, Y:%f Z: %f"), SunLocationY, SunLocationZ);
			SunLocationZ = 0.0f;
			SunLocationY = 0.0f;
		}
		
		//Its Sunset
		else if (DayTimeEndsInMinutes <= CurrentTimeInMinutes && CurrentTimeInMinutes <= (DayTimeEndsInMinutes + 60))
		{
			UE_LOG(LogTemp, Error, TEXT("Its Sunset, Y:%f Z: %f"), SunLocationY, SunLocationZ);
			SunLocationZ = 0.0f;
			SunLocationY = 0.0f;
		}
		else
		{
			//Its night
			UE_LOG(LogTemp, Error, TEXT("Its night, Y:%f Z: %f"), SunLocationY, SunLocationZ);
			SunLocationZ = 0.0f;
			SunLocationY = 0.0f;
		}
		
		
		bSunSetToCurrentTime = true;

	/*


	//Check what time it is, and where the sun should be.

	//How many angle to add should have been added. AngleToAddOnY * ? = Wanted result
	//? = How many ticks there have been

	//If the sun has been set correctly, just add to it. 
	if(bSunSetToCurrentTime)
	{
		SunLocationZ = SunLocationZ + AngleToAddOnZ;

	}
	else
	{
	

	}
	
	if(bIsDayTime)
	{
		

		if(bSunGoesDone)
		{
			SunLocationY = SunLocationY - AngleToAddOnY;
		}
		else
		{
			SunLocationY = SunLocationY + AngleToAddOnY;
		}
	}
	else
	{
		//This is not oke
		SunLocationZ = SunRisingPosition + AngleToAddOnZ;
		SunLocationY = SunPositionLowestPoint + AngleToAddOnY;
		bIsDayTime = true;
	}

	//Check if day ended.
	if (SunLocationY >= SunPositionHighestPoint)
	{
		bSunGoesDone = true;
	}
	else if(SunLocationY <= SunPositionLowestPoint)
	{
		bSunGoesDone = false;
	}

	if (SunLocationZ >= SunSettingPosition)
	{
		bIsDayTime = false;
	}
	*/
	if(SunLigth)
	{
		SunLigth->SetActorRelativeRotation(FRotator(SunLocationY, SunLocationZ, 0.0f));
	}	
}
