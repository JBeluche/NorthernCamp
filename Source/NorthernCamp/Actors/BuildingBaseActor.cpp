// Fill out your copyright notice in the Description page of Project Settings.


#include "NorthernCamp/Actors/BuildingBaseActor.h"

// Sets default values
ABuildingBaseActor::ABuildingBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABuildingBaseActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABuildingBaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

