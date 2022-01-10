// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "Components/SphereComponent.h"
#include "NorthernCamp/Actors/BuildingBaseActor.h"

#include "CharacterSettler.generated.h"


class ADayNightActorController;

enum class ESettlerSchedule : uint8 
{
	None UMETA(DisplayName = "None"),
	Work UMETA(DisplayName = "Work"),
	Sleep UMETA(DisplayName = "Sleep"),
	Leisure UMETA(DisplayName = "Leisure"),

};

UENUM(BlueprintType)
enum class EWorkType : uint8 
{
	None UMETA(DisplayName = "None"),
	Building UMETA(DisplayName = "Building"),
	Gather UMETA(DisplayName = "Gather"),

};

USTRUCT(BlueprintType)
struct FCurrentWork
{
	GENERATED_BODY()
	
	EWorkType WorkType;

	EResourceType ResourceToGather;

	ABuildingBaseActor* WorkBuilding;
};



enum class EResourceType : uint8;
class UVitalsComponent;

UCLASS()
class NORTHERNCAMP_API ACharacterSettler : public ACharacterBase
{
	GENERATED_BODY()

public:
	ACharacterSettler();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;
	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	UVitalsComponent* VitalsComponent;

	UVitalsComponent* GetCharacterVitalsComponent();

	bool bIsHero = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	float ActionRange = 100.0f;


//Public variables
	UResourceManagerComponent* ResourceManagerComp;

	int32 WorkHoursAmount = 12;
	int32 FunHoursAmount = 3;
	int32 SleepHoursAmount = 9;

	ESettlerSchedule CurrentSchedule;
	ABuildingBaseActor* CurrentResidence;
	FCurrentWork CurrentWork;


//Public functions
	bool DrinkWater(float Amount);
	bool CheckIfResourceInHand(EResourceType ResourceType, int32 Amount);
	bool PutResourceInHand(EResourceType ResourceType, int32 Amount);

	void ResetCurrentWork();

	ADayNightActorController* DayNightActorController;
	
	UFUNCTION() 
	void HourStruck(float CurrentHour);

private:
	//Can be item, resource or else?
	EResourceType ResourceHandLeft = EResourceType::None;
	EResourceType ResourceHandRight = EResourceType::None;;
	int32 ResourceAmountHandRight = 0;
	int32 ResourceAmountHandLeft = 0;

	//Private functions
	void DropResource();

protected:
	virtual void BeginPlay() override;

	void UpdateSchedule(float CurrentHour);
};
