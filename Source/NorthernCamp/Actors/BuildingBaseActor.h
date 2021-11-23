// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "BuildingBaseActor.generated.h"


enum class EResourceType : uint8 
{
	Water UMETA(DisplayName = "Water"),
	Food UMETA(DisplayName = "Food"),
	
};


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

	TMap<EResourceType, int32> ResourcesStoredInBuilding;
	TMap<EResourceType, int32> BuildingCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
	int32 StartingWater;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
	USphereComponent* BuildingActionRadius;

	bool ExtractRersouce(EResourceType ResourceType, int32 Amount);
	bool CheckResourceAvailability(EResourceType ResourceType, int32 Amount);
};
