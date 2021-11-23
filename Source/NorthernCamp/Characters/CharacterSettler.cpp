// Fill out your copyright notice in the Description page of Project Settings.


#include "NorthernCamp/Characters/CharacterSettler.h"
#include "NorthernCamp/CharacterComponents/VitalsComponent.h"


ACharacterSettler::ACharacterSettler()
{
	VitalsComponent = CreateDefaultSubobject<UVitalsComponent>(TEXT("Vitals Component"));

}

UVitalsComponent* ACharacterSettler::GetCharacterVitalsComponent()
{
	return VitalsComponent;
}

void ACharacterSettler::Drink()
{

	UE_LOG(LogTemp, Error, TEXT("Hi, i am not happy"));
	
	//VitalsComponent->CurrentWaterMeter = 100.f;
}