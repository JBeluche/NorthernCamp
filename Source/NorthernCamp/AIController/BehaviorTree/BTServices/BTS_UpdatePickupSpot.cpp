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

	//Get the ActorWithResource and check if the pickup spot is still his. Reset all values if it is'nt. Update the values if it is.

	AActor* Actor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("ActorWithResource")));

	if(Actor)
	{
		UResourcesPickupSpot* PickupComponent = Cast<UResourcesPickupSpot>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("PickupComponent")));

		
		
		if(PickupComponent)
		{
			//Check if the component is still the one from the current actor.
			if(PickupComponent->GetOwner() != Actor)
			{
				OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("PickupComponent"));
				OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("PickupLocation"));
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
}
