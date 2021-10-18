// Copyright Creating Mountains!


#include "NorthernCamp/Controllers/DayNightActorController.h"
#include "Engine/DirectionalLight.h"


// Sets default values
ADayNightActorController::ADayNightActorController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADayNightActorController::BeginPlay()
{
	Super::BeginPlay();

	//Start the time timer
	SetTimeTo(StartingHour, 0.0f);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ADayNightActorController::MoveTime, TimeUpdatesInterval, true);

	TotalDayTimeInVirtualMinutes = (SunsetHour - SunriseHour) * 60;
	AngleToAdd = (SunSettingPosition - SunRisingPosition) / ((SecondsPerHour / TimeUpdatesInterval) * (SunsetHour - SunriseHour));

	
}

// Called every frame
void ADayNightActorController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ADayNightActorController::SetTimeTo(float HourToSet, float MinuteToSet)
{
	CurrentTimeMinutes = MinuteToSet;
	CurrentTimeHours = HourToSet;
}

void ADayNightActorController::MoveTime()
{
	//Check time speed and move time according to a calculation
	CurrentTimeMinutes = CurrentTimeMinutes + (60.0f / (SecondsPerHour / TimeUpdatesInterval));

	
	Ticker++;

	if(CurrentTimeMinutes >= 60.0f)
	{
		CurrentTimeHours++;
		if(CurrentTimeHours >= 24.0f){CurrentTimeHours = 0.0f;}
		if(CurrentTimeMinutes > 60.0f){CurrentTimeMinutes = 60.0f / (SecondsPerHour / TimeUpdatesInterval);}
		else{CurrentTimeMinutes = 0.0f;}
	}
	UE_LOG(LogTemp, Error, TEXT("Current Time: %f:%f"), FMath::RoundHalfToZero(CurrentTimeHours), FMath::RoundHalfToZero(CurrentTimeMinutes));

	
	


	//Check if its daytime otherwise set it on.
	if(bIsDayTime)
	{
		SunLocationZ = SunLocationZ + AngleToAdd;

	}
	else
	{
		SunLocationZ = SunRisingPosition + AngleToAdd;
		bIsDayTime = true;
	}

	//Check if day ended.
	if (SunLocationZ >= SunSettingPosition)
	{
		bIsDayTime = false;

	}
	
	UE_LOG(LogTemp, Error, TEXT("Sun position z: %f adding: %f SunRisingPosition: %f, SunLocationZ %f"), SunLigth->GetActorRotation().Yaw, AngleToAdd, SunRisingPosition, SunLocationZ);
	if(SunLigth)
	{
		SunLigth->SetActorRelativeRotation(FRotator(200.0f, SunLocationZ, 0.0f));
	}
	

	
}
