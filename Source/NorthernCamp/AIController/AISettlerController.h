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

		void CheckTodoAtBuilding();

		//Water
		void WaterIsLow();

/*
		UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
		
		UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
*/

	protected:

		ABuildingBaseActor* OverlappingBuilding;
		
		UPROPERTY()
		UNavigationSystemV1* NavigationSystemv1;

		void UnFreeze();
		void SettlerIsBusy(/*Animation type*/ bool ShouldFreeze, float Duration);

		UFUNCTION()
		void GetClosestStockedResourceLocation(UEnum* ResourceType, int32 AmountNeeded);
		
		//Timers
		FTimerManager* CurrentTimerManager;

		FTimerHandle CharacterSearchesForWaterTimerHandle;
		FTimerHandle CharacterFrozenTimerHandle;
		FTimerHandle TodoAtBuildingTimerHandle;
	
};


	
