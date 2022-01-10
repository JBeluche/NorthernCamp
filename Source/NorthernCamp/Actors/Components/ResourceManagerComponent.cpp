// Copyright Creating Mountains!


#include "NorthernCamp/Actors/Components/ResourceManagerComponent.h"

#include "ResourcesPickupSpot.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "NorthernCamp/NorthernCampGameMode.h"
#include "NorthernCamp/Characters/CharacterSettler.h"

// Sets default values for this component's properties
UResourceManagerComponent::UResourceManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;


     
}


// Called when the game starts
void UResourceManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	


	

	AActor* Owner = Cast<AActor>(GetOwner());
	if(Owner)
	{
		TInlineComponentArray<UResourcesPickupSpot*> Components;
		Owner->GetComponents(Components);
	
		for (auto CompIt = Components.CreateConstIterator(); CompIt; ++CompIt)
		{
			PickupLocations.Emplace(Cast<UResourcesPickupSpot>(*CompIt), nullptr);
		}

		//Register self to game state as a resource actor;
		
		ANorthernCampGameMode * GameMode = Cast<ANorthernCampGameMode>(GetWorld()->GetAuthGameMode());
		GameMode->AddResourceManager(this);
	}

}
void UResourceManagerComponent::AddResource(EResourceType ResourceType, int32 Amount)
{
	if(ResourcesInStorage.Contains(ResourceType))
	{
		ResourcesInStorage.Emplace(ResourceType, (CurrentResourceNeeded[ResourceType] + Amount));
	}
	else
	{
		ResourcesInStorage.Add(ResourceType, Amount);
	}
}

bool UResourceManagerComponent::ExtractRersouce(EResourceType ResourceType, int32 Amount, ACharacter* Character)
{

	//This is just for debuging
	FString EnumName;
	const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EResourceType"), true);
	if (!enumPtr)
	{
		EnumName = FString("Invalid");
	}
	else
	{
		EnumName = enumPtr->GetNameStringByIndex((int32)ResourceType);
	}
	
	//End debug shit
	bool ResourceIsAvailable = CheckResourceAvailability(ResourceType, Amount);
	
	if(ResourceIsAvailable)
	{
		if(EndlessResourceList.Contains(ResourceType))
		{
			
		     //ResourcesInStorage.Emplace(ResourceType, (CurrentResourceNeeded[ResourceType] - Amount));
			FreePickupSpot(Character);
			return true;
		}
		
		for (TPair<EResourceType, int32>& Pair : ResourcesInStorage)
		{
			if(Pair.Key == ResourceType && Pair.Value >= Amount)
			{
				ResourcesInStorage.Emplace(Pair.Key, (Pair.Value - Amount));
				UE_LOG(LogTemp, Warning, TEXT("%s took: %s | %i From: %s Current Resource in Stock: %i"), *Character->GetName(), *EnumName, Amount, *GetName(), Pair.Value);
				FreePickupSpot(Character);

				return true;
			}
		}
	}
	
	return false;
}

bool UResourceManagerComponent::CheckResourceAvailability(EResourceType ResourceType, int32 Amount)
{
	//Might cause a crash if the array does not exists but he tries to compare with the amount.
	if(EndlessResourceList.Contains(ResourceType))
	{
		return true;
	}
	for (TPair<EResourceType, int32>& Pair : ResourcesInStorage)
	{
		if(Pair.Key == ResourceType && Pair.Value >= Amount)
		{
			return true;
		}
	}
	
	return false;
}

//When almost at the cart location reserve the spot so other characters can look for another
UResourcesPickupSpot* UResourceManagerComponent::ReservePickupSpot(ACharacter* CharacterAskingForSpot, UResourcesPickupSpot* PreferableSpot)
{
	UResourcesPickupSpot* Spot;
	Spot = FindReservedPickupSpot(CharacterAskingForSpot);
	
	
	if(Spot != nullptr)
	{
		return Spot;
	}
	else
	{
		//Try and get preferable spot, if you can then set it
		if(PickupLocations[PreferableSpot] == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Preferable spot reserved for: %s"), *CharacterAskingForSpot->GetName());

			PickupLocations.Emplace(PreferableSpot, CharacterAskingForSpot);
			Spot = PreferableSpot;
		}
		else
		{
			for (TPair<UResourcesPickupSpot*, AActor*>& Pair : PickupLocations)
			{
				if(Pair.Value == nullptr)
				{
					PickupLocations.Emplace(Pair.Key, CharacterAskingForSpot);
					UE_LOG(LogTemp, Error, TEXT("Other spot reserved for: %s"), *CharacterAskingForSpot->GetName());
					return Pair.Key;
				}
			}
		}
	
		
		
		return Spot;
	}
}

UResourcesPickupSpot* UResourceManagerComponent::FindReservedPickupSpot(ACharacter* CharacterAskingForSpot)
{
	//Check if the character already is in tmap
	for (TPair<UResourcesPickupSpot*, AActor*>& Pair : PickupLocations)
	{
		if(Pair.Value != nullptr)
		{
			if(Pair.Value == CharacterAskingForSpot)
			{
				return Pair.Key;
			}
		}
	}

	return nullptr;
}

UResourcesPickupSpot* UResourceManagerComponent::FreePickupSpot(ACharacter* CharacterAskingForSpot)
{
	//Check if the character already is in tmap
	for (TPair<UResourcesPickupSpot*, AActor*>& Pair : PickupLocations)
	{
		if(Pair.Value == CharacterAskingForSpot)
		{
			UE_LOG(LogTemp, Error, TEXT("Spot deleted by: %s"), *CharacterAskingForSpot->GetName());

			Pair.Value = nullptr; 
		}
	}

	return nullptr;
}


void UResourceManagerComponent::AddResourceNeed(EResourceType ResourceType, int32 Amount)
{
	if(EndlessResourceList.Contains(ResourceType))
	{
		UE_LOG(LogTemp, Error, TEXT("%s: I am trying to add a resource need, but have an endless supply."), *GetOwner()->GetName())
	}
	
	if(CurrentResourceNeeded.Contains(ResourceType))
	{
		CurrentResourceNeeded.Emplace(ResourceType, (CurrentResourceNeeded[ResourceType] + Amount));
	}
	else
	{
		CurrentResourceNeeded.Add(ResourceType, Amount);
	}
}


void UResourceManagerComponent::AddEndlessResource(EResourceType ResourceType)
{
	if(!EndlessResourceList.Contains(ResourceType))
	{
		EndlessResourceList.Add(ResourceType);
	}
}

FResourceNeedStruct UResourceManagerComponent::GetResourceNeed()
{
	
	FResourceNeedStruct ResourcesNeeded;
	
	if(CurrentResourceNeeded.Num() > 0)
	{
		//Decide what resource to send?
		if(CurrentResourceNeeded.Contains(EResourceType::Water))
		{
			ResourcesNeeded.ResourceType = EResourceType::Water;
			ResourcesNeeded.Amount = CurrentResourceNeeded[EResourceType::Water];
		}
		else if(CurrentResourceNeeded.Contains(EResourceType::Water))
		{
			ResourcesNeeded.ResourceType = EResourceType::Food;
			ResourcesNeeded.Amount = CurrentResourceNeeded[EResourceType::Food];
		}
		
	}

	return ResourcesNeeded;
}

