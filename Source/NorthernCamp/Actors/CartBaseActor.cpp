// Copyright Creating Mountains!


#include "NorthernCamp/Actors/CartBaseActor.h"

#include "Components/BoxComponent.h"
#include "NorthernCamp/Actors/BuildingBaseActor.h"

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
	for (const TPair<EResourceType, int32>& Pair : ResourcesStoredInCart)
	{
		if(Pair.Key == ResourceType && Pair.Value >= Amount)
		{
			ResourcesStoredInCart.Emplace(Pair.Key, (Pair.Value - Amount));
			UE_LOG(LogTemp, Warning, TEXT("Took water from the cart, current water: %i"), Pair.Value);
			
			return true;
		}
	}
	
	return false;
}

bool ACartBaseActor::CheckResourceAvailability(EResourceType ResourceType, int32 Amount)
{
	for (const TPair<EResourceType, int32>& Pair : ResourcesStoredInCart)
	{
		if(Pair.Key == ResourceType && Pair.Value >= Amount)
		{
			return true;
		}
	}
	return false;
}

//When almost at the cart location reserve the spot so other characters can look for another
bool ACartBaseActor::ReservePickupSpot(AActor* ActorAskingForSpot)
{
	for (const TPair<UBoxComponent*, AActor*>& Pair : PickupLocations)
	{
		if(Pair.Value == nullptr)
		{
			PickupLocations.Emplace(Pair.Key, ActorAskingForSpot);
			UE_LOG(LogTemp, Warning, TEXT("A spot(%s) was reserved by: %s"), *Pair.Key->GetName(), *Pair.Value->GetName());
			
			return true;
		}
	}
	return false;
}



