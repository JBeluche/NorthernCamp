// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "Components/SphereComponent.h"
#include "NorthernCamp/Actors/BuildingBaseActor.h"

#include "CharacterSettler.generated.h"

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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	UVitalsComponent* VitalsComponent;

	UVitalsComponent* GetCharacterVitalsComponent();

	bool bIsHero = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	float ActionRange = 100.0f;


//Public variables
	UResourceManagerComponent* ResourceManagerComp;

	int32 WorkHoursAmount;
	int32 FunHoursAmount;
	int32 SleepHoursAmount;
	

//Public functions
	bool DrinkWater(float Amount);
	bool CheckIfResourceInHand(EResourceType ResourceType, int32 Amount);
	bool PutResourceInHand(EResourceType ResourceType, int32 Amount);

private:
	//Can be item, resource or else?
	EResourceType ResourceHandLeft = EResourceType::None;
	EResourceType ResourceHandRight = EResourceType::None;;
	int32 ResourceAmountHandRight = 0;
	int32 ResourceAmountHandLeft = 0;

	//Private functions
	void DropResource();
};
