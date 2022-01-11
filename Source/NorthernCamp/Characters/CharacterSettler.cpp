// Fill out your copyright notice in the Description page of Project Settings.


#include "NorthernCamp/Characters/CharacterSettler.h"

#include "EngineUtils.h"
#include "NorthernCamp/CharacterComponents/VitalsComponent.h"


ACharacterSettler::ACharacterSettler()
{
	VitalsComponent = CreateDefaultSubobject<UVitalsComponent>(TEXT("Vitals Component"));
	ResourceManagerComp = CreateDefaultSubobject<UResourceManagerComponent>(TEXT("Resource Manager"));


}
void ACharacterSettler::BeginPlay()
{
	Super::BeginPlay();


	for (TActorIterator<ADayNightActorController> ActorItr(GetWorld()); ActorItr; ++ActorItr) 
	{ 
		DayNightActorController = Cast<ADayNightActorController>(*ActorItr); 
	}
	
	if(DayNightActorController) 
	{ 
		WorkHoursAmount = 12;
		FunHoursAmount = 3;
		SleepHoursAmount = 9;

		HourStruck(DayNightActorController->CurrentTimeHours);

		
		DayNightActorController->AnHourStruck.AddDynamic(this, &ACharacterSettler::HourStruck); 
	}
	
}

void ACharacterSettler::HourStruck(float CurrentHour) 
{
	UpdateSchedule(CurrentHour);
}

void ACharacterSettler::UpdateSchedule(float CurrentHour)
{
	if(CurrentHour >= 6.0f && CurrentHour < (6.0f + WorkHoursAmount))
	{
		CurrentSchedule = ESettlerSchedule::Work;
	}
	else if(CurrentHour < 6.0f || CurrentHour >= (6.0f + WorkHoursAmount + FunHoursAmount))
	{
		CurrentSchedule = ESettlerSchedule::Sleep;
	}
	else
	{
		CurrentSchedule = ESettlerSchedule::Leisure;
	}
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


void ACharacterSettler::ResetCurrentWork()
{
	if(CurrentWork.WorkBuilding != nullptr)
	{
		ABuildingBaseActor* Building = CurrentWork.WorkBuilding;
		Building->RemoveWorker(this);
	}

	CurrentWork.WorkBuilding = nullptr;
	CurrentWork.WorkType = EWorkType::None;
	CurrentWork.ResourceToGather = EResourceType::None;
	
}

void ACharacterSettler::ResetCurrentResidence()
{
	CurrentResidence->RemoveInhabitant(this);
	CurrentResidence = nullptr;
}


