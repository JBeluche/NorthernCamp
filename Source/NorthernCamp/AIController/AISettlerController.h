// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "AIControllerBase.h"
#include "NorthernCamp/Actors/BuildingBaseActor.h"
#include "NorthernCamp/Characters/CharacterSettler.h"

#include "NavigationSystem.h"

#include "AISettlerController.generated.h"


UENUM()
enum class ECurrentTask : uint8 
{
	Frozen UMETA(DisplayName = "Frozen"),
	ConsumeResource UMETA(DisplayName = "ConsumeResource"),
	FetchingResource UMETA(DisplayName = "FetchingResource"),
	Work UMETA(DisplayName = "Work"),
	Sleep UMETA(DisplayName = "Sleep"),
	HaveFun UMETA(DisplayName = "HaveFun"),

};



UCLASS()
class NORTHERNCAMP_API AAISettlerController : public AAIControllerBase
{
	GENERATED_BODY()
	
	public:


	AAISettlerController();
	
	ACharacterSettler* CharacterOwner;

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBehaviorTree* BehaviorTree;

	ADayNightActorController* DayNightActorController;

	UFUNCTION()
	void HourStruck(float CurrentHour);
	//Water
	void WaterIsLow();

};


	
