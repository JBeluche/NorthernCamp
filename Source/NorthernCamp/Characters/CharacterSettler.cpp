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
