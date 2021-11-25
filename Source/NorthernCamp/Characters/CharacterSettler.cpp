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

bool ACharacterSettler::DrinkWater(float Amount)
{
	if(VitalsComponent)
	{
		VitalsComponent->CurrentWaterMeter = Amount;
		return true;
	}

	return false;
}

bool ACharacterSettler::CheckIfResourceInHand(EResourceType ResourceType, int32 Amount)
{
	if(ResourceType == ResourceHandLeft || ResourceType == ResourceHandRight)
	{
		if(Amount > ResourceAmountHandLeft || Amount > ResourceAmountHandRight)
		{
			return false;
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool ACharacterSettler::PutResourceInHand(EResourceType ResourceType, int32 Amount)
{
	if(CheckIfResourceInHand(ResourceType, Amount))
	{
		DropResource();
	}
	
	ResourceHandRight = ResourceType;
	ResourceAmountHandRight = Amount;

	return true;
}

void ACharacterSettler::DropResource()
{
	ResourceHandLeft = EResourceType::None;
	ResourceHandRight = EResourceType::None;
	ResourceAmountHandRight = 0;
	ResourceAmountHandLeft = 0;
}