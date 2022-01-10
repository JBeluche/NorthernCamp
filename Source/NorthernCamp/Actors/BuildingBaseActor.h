// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ResourceManagerComponent.h"

#include "GameFramework/Actor.h"
#include "BuildingBaseActor.generated.h"


class ACharacterSettler;
class UWorkingSpot;
class USleepingSpot;
UCLASS()
class NORTHERNCAMP_API ABuildingBaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuildingBaseActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	int32 StartingFood;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	int32 StartingWater;

	
	TMap<EResourceType, int32> BuildingCost;
	
	UResourceManagerComponent* ResourceManagerComp;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building")
	TArra SleepingSpots;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building")
	int32 WorkingSpotsAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building")
	FSlateBrush BuildingIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building")
	FText BuildingName;
	
	TMap<USleepingSpot*, ACharacter*> SleepingSpots;
	TMap<UWorkingSpot*, ACharacterSettler*> WorkingSpots;

	//Public functions
		USleepingSpot* AddInhabitant(ACharacter* Settler);
		void RemoveInhabitant(ACharacter* Settler);
		TArray<USleepingSpot*> GetFreeSleepingSpots();
		
		void RemoveWorker(ACharacterSettler* Settler);
		UWorkingSpot* AddWorker(ACharacterSettler* Settler);
		TArray<UWorkingSpot*> GetFreeWorkingSpot();

};
