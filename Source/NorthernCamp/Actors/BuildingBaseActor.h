// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ResourceManagerComponent.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "BuildingBaseActor.generated.h"





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

	
};
