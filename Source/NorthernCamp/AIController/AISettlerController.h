// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "AIControllerBase.h"
#include "NorthernCamp/Actors/BuildingBaseActor.h"
#include "NorthernCamp/Characters/CharacterSettler.h"

#include "NavigationSystem.h"

#include "AISettlerController.generated.h"


UENUM(BlueprintType)
enum class ECurrentTask : uint8 
{
	Diner UMETA(DisplayName = "Diner"),
	GettingFood UMETA(DisplayName = "Getting Food"),
	GoingToWork UMETA(DisplayName = "Going to Work"),
	GoingToSleep UMETA(DisplayName = "Going to Sleep"),
	GoingToCampfire UMETA(DisplayName = "Going to Campfire"),
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


	