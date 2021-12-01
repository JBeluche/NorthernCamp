// Copyright Creating Mountains!


#include "NorthernCamp/AIController/BehaviorTree/BTServices/BTS_CheckResourceAvailability.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NorthernCamp/Actors/CartBaseActor.h"
#include "NorthernCamp/Actors/DrinkingPlaceActor.h"
#include "NorthernCamp/Characters/CharacterSettler.h"


UBTS_CheckResourceAvailability::UBTS_CheckResourceAvailability()
{
	NodeName = "Check if resource available";
}

void UBTS_CheckResourceAvailability::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
	
	AActor* Actor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("PickupActor")));
	
	bool bHasResources = false;

	if(Actor)
	{
		UResourceManagerComponent* ResourceManagerComp = Cast<UResourceManagerComponent>(Actor->GetComponentByClass(UResourceManagerComponent::StaticClass()));
		if(ResourceManagerComp)
		{
			ResourceManagerComp->CheckResourceAvailability(EResourceType::Water, 1);
		}
	}
	

	
	
	if(bHasResources)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("PickupActor"));
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}

	


}
