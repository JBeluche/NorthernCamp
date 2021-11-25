// Copyright Creating Mountains!


#include "NorthernCamp/Actors/CartBaseActor.h"

#include "Components/BoxComponent.h"
#include "NorthernCamp/Actors/BuildingBaseActor.h"
#include "NorthernCamp/Characters/CharacterSettler.h"

//////
// FEATURES IDEAS
//-Reserve resource for incoming settler



// Sets default values
ACartBaseActor::ACartBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);
	
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	MeshComp->SetupAttachment(SceneComponent);

	ResourceManagerComp = CreateDefaultSubobject<UResourceManagerComponent>(TEXT("Resource Manager"));
	
	
}

// Called when the game starts or when spawned
void ACartBaseActor::BeginPlay()
{
	Super::BeginPlay();

	ResourcesStoredInCart.Add(EResourceType::Water, StartingWater);
	ResourcesStoredInCart.Add(EResourceType::Food, 10);


	//Get all the box component and set them in a tmap with a bool. This way they will act as spots where characters can go to. 
	TInlineComponentArray<UBoxComponent*> Components;
	GetComponents(Components);
	for (auto CompIt = Components.CreateConstIterator(); CompIt; ++CompIt)
	{
		PickupLocations.Emplace(Cast<UBoxComponent>(*CompIt), nullptr);
	}

}

bool ACartBaseActor::ExtractRersouce(EResourceType ResourceType, int32 Amount)
{
	for (TPair<EResourceType, int32>& Pair : ResourcesStoredInCart)
	{
		if(Pair.Key == ResourceType && Pair.Value >= Amount)
		{
			ResourcesStoredInCart.Emplace(Pair.Key, (Pair.Value - Amount));
			UE_LOG(LogTemp, Warning, TEXT("%s 's current water: %i"), *GetName(), Pair.Value);
			
			return true;
		}
	}
	
	return false;
}

bool ACartBaseActor::CheckResourceAvailability(EResourceType ResourceType, int32 Amount)
{
	for (TPair<EResourceType, int32>& Pair : ResourcesStoredInCart)
	{
		if(Pair.Key == ResourceType && Pair.Value >= Amount)
		{
			return true;
		}
	}
	return false;
}

//When almost at the cart location reserve the spot so other characters can look for another
UBoxComponent* ACartBaseActor::ReservePickupSpot(ACharacterSettler* CharacterAskingForSpot)
{
	UBoxComponent* Spot = FindReservedPickupSpot(CharacterAskingForSpot);
	if(Spot != nullptr)
	{
		return Spot;
	}
	else
	{
		for (TPair<UBoxComponent*, AActor*>& Pair : PickupLocations)
		{
			if(Pair.Value == nullptr)
			{
				PickupLocations.Emplace(Pair.Key, CharacterAskingForSpot);
				UE_LOG(LogTemp, Error, TEXT("Spot reserved for: %s"), *CharacterAskingForSpot->GetName());
				return Pair.Key;
			}
			
		}
		if(CheckResourceAvailability(EResourceType::Water, 1))
		{
			UE_LOG(LogTemp, Error, TEXT("We are full, but have water!!"));
				
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("We are full, without resources!!"));

		}
		
		return nullptr;
	}
}

UBoxComponent* ACartBaseActor::FindReservedPickupSpot(ACharacterSettler* CharacterAskingForSpot)
{
	//Check if the character already is in tmap
	for (TPair<UBoxComponent*, AActor*>& Pair : PickupLocations)
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

UBoxComponent* ACartBaseActor::FreePickupSpot(ACharacterSettler* CharacterAskingForSpot)
{
	//Check if the character already is in tmap
	for (TPair<UBoxComponent*, AActor*>& Pair : PickupLocations)
	{
		if(Pair.Value == CharacterAskingForSpot)
		{
			UE_LOG(LogTemp, Error, TEXT("Spot deleted by: %s"), *CharacterAskingForSpot->GetName());

			Pair.Value = nullptr; 
		}
	}

	return nullptr;
}


