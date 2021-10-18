// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DayNightActorController.generated.h"

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
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ADirectionalLight* SunLigth;

	FTimerHandle TimerHandle;

	float CurrentTimeMinutes;
	float CurrentTimeHours;

	float SunLocationZ;
	float TotalDayTimeInVirtualMinutes;

	bool bIsDayTime;

	
	int Ticker;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SunriseHour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SunsetHour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SunRisingPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SunSettingPosition;

	float AngleToAdd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SecondsPerHour;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StartingHour;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeUpdatesInterval;
	
	void SetTimeTo(float HourToSet, float MinuteToSet);

	void MoveTime();
	
};
