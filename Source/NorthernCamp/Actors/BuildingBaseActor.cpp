// Fill out your copyright notice in the Description page of Project Settings.


#include "NorthernCamp/Actors/BuildingBaseActor.h"

// Sets default values
ABuildingBaseActor::ABuildingBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ResourceManagerComp = CreateDefaultSubobject<UResourceManagerComponent>(TEXT("Resource Manager"));

}

// Called when the game starts or when spawned
void ABuildingBaseActor::BeginPlay()
{
	Super::BeginPlay();

	ResourceManagerComp->AddResource(EResourceType::Water, StartingWater);
	ResourceManagerComp->AddResource(EResourceType::Food, StartingFood);
}

