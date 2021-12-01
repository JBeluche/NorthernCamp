// Copyright Creating Mountains!


#include "NorthernCamp/AIController/BehaviorTree/BTServices/BTS_UpdateWaterLocation.h"

#include "EngineUtils.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NorthernCamp/NorthernCampGameMode.h"
#include "NorthernCamp/Actors/CartBaseActor.h"
#include "NorthernCamp/Actors/DrinkingPlaceActor.h"
#include "NorthernCamp/AIController/AISettlerController.h"
#include "UObject/UObjectIterator.h"


UBTS_UpdateWaterLocation::UBTS_UpdateWaterLocation()
{
	NodeName = "Update Water Actor and Location";
}

void UBTS_UpdateWaterLocation::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) 
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAISettlerController* Controller = Cast<AAISettlerController>(OwnerComp.GetAIOwner());
	ACharacterSettler* Settler = Cast<ACharacterSettler>(Controller->GetPawn());
	AActor* ClosestActorWithWater = nullptr;
	FVector PickupLocation;
	UResourcesPickupSpot* PikcupSpotPtr = nullptr;
	NavigationSystemv1 = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	
	if(NavigationSystemv1)
	{
		if(Controller != nullptr || Settler != nullptr)
		{
			float NewPathLength;
			float OldPathLength;

			EResourceType ResourcesNeeded = Settler->ResourceManagerComp->GetResourceNeed().ResourceType;
			int32 ResourceAmountNeeded = Settler->ResourceManagerComp->GetResourceNeed().Amount;

			ANorthernCampGameMode * GameMode = Cast<ANorthernCampGameMode>(GetWorld()->GetAuthGameMode());
		
			
			if(GameMode)
			{
				for (UResourceManagerComponent* ResourceManagerComp : GameMode->ResourceManagerComps)
				{
					//Iterate all the spots
					for (auto& PickupSpot : ResourceManagerComp->PickupLocations)
					{

						NavigationSystemv1->GetPathLength(Settler->GetActorLocation(), PickupSpot.Key->GetComponentLocation(), NewPathLength);

						if(ClosestActorWithWater == nullptr && ResourceManagerComp->CheckResourceAvailability(ResourcesNeeded, ResourceAmountNeeded))
						{
							PikcupSpotPtr = PickupSpot.Key;
							ClosestActorWithWater = ResourceManagerComp->GetOwner();
							OldPathLength = NewPathLength;

						}
						else if(NewPathLength < OldPathLength && ResourceManagerComp->CheckResourceAvailability(ResourcesNeeded, ResourceAmountNeeded))
						{
							PikcupSpotPtr = PickupSpot.Key;
							ClosestActorWithWater = ResourceManagerComp->GetOwner();
							OldPathLength = NewPathLength;
						}
					}
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Casting failed in BTS_UpdateWaterLocation"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("A settler is not finding the navigation system"));
	}

	if(ClosestActorWithWater)
	{
		UE_LOG(LogTemp, Error, TEXT("Going for: %s"), *ClosestActorWithWater->GetName());

		OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("PickupActor"), ClosestActorWithWater);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("bResourceStillAvailable"), true);
		
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("PreferablePickupSpot"), PikcupSpotPtr);
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PikcupSpotPtr->GetComponentLocation());
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("bResourceStillAvailable"), false);
	}

}
