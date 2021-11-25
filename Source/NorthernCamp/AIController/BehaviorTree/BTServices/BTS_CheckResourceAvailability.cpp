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
	//Get the pickup actor
	//Check if the resource is still avaible
	
	ACharacterSettler* Settler  = Cast<ACharacterSettler>(OwnerComp.GetAIOwner()->GetPawn());
	
	AActor* Actor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("PickupActor")));
	
	//Cast to cart, building, watersource
	ABuildingBaseActor* Building = Cast<ABuildingBaseActor>(Actor);
	ACartBaseActor* Cart = Cast<ACartBaseActor>(Actor);
	ADrinkingPlaceActor* WaterSource = Cast<ADrinkingPlaceActor>(Actor);

	bool bHasResources = false;

	if(WaterSource)
	{


	}
	else if(Cart)
	{
		bHasResources = Cart->CheckResourceAvailability(EResourceType::Water, 1);
	}
	else if(Building)
	{
		
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
