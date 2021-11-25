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
	
	ACartBaseActor* Cart = Cast<ACartBaseActor>(Actor);

	//Check if the pickup actor still has water. If he has, do nothing.
	bool StillHasWater = false;
	
	if(Cart)
	{
		StillHasWater = Cart->CheckResourceAvailability(EResourceType::Water,1 );
	}
	
	//Else delete all the coresponding 
	if(StillHasWater)
	{
		UBoxComponent* PickupComponent = Cast<UBoxComponent>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("PickupComponent")));
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
