// Copyright Creating Mountains!


#include "NorthernCamp/AIController/BehaviorTree/BTServices/BTS_UpdatePickupSpot.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Components/BoxComponent.h"
#include "NorthernCamp/Actors/CartBaseActor.h"
#include "NorthernCamp/Actors/BuildingBaseActor.h"


UBTS_UpdatePickupSpot::UBTS_UpdatePickupSpot()
{
	NodeName = "Update Pickup spot";
}

void UBTS_UpdatePickupSpot::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AActor* Actor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("PickupActor")));
	bool StillHasWater = false;

	//UResourceManagerComponent* ResourceManagerComp = Cast<UResourceManagerComponent>(Actor->GetComponentByClass(TSubclassOf<UResourceManagerComponent> ComponentClass));
	if(Actor)
	{
		UResourceManagerComponent* ResourceManagerComp = Cast<UResourceManagerComponent>(Actor->GetComponentByClass(UResourceManagerComponent::StaticClass()));
		if(ResourceManagerComp)
		{
			StillHasWater = ResourceManagerComp->CheckResourceAvailability(EResourceType::Water,1 );
		}
	}
	
	if(StillHasWater)
	{
		UResourcesPickupSpot* PickupComponent = Cast<UResourcesPickupSpot>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("PickupComponent")));
		
		if(PickupComponent)
		{
			//Check if the component is still the one from the current actor.
			if(PickupComponent->GetOwner() != Actor)
			{
				OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("PickupComponent"));
				OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("PickupLocation"));
				OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("PickupActor"));
			}
			else
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("PickupLocation"), PickupComponent->GetComponentLocation());
			}
		}
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("PickupComponent"));
		OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("PickupLocation"));
		OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("PickupActor"));
	}

	//Reset the current location of the pickupspot for if it is moving it changes.
	

}
