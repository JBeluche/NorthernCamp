// Copyright Creating Mountains!


#include "NorthernCamp/AIController/BehaviorTree/BTTAsks/BTT_FreePickupSpot.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NorthernCamp/Actors/CartBaseActor.h"
#include "NorthernCamp/Actors/DrinkingPlaceActor.h"
#include "NorthernCamp/Characters/CharacterSettler.h"

UBTT_FreePickupSpot::UBTT_FreePickupSpot()
{
	NodeName = TEXT("Free pickup spot");
}

EBTNodeResult::Type UBTT_FreePickupSpot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACharacterSettler* Settler  = Cast<ACharacterSettler>(OwnerComp.GetAIOwner()->GetPawn());
	
	//Cast to cart, building, watersource
	/*ABuildingBaseActor* Building = Cast<ABuildingBaseActor>(Actor);
	ACartBaseActor* Cart = Cast<ACartBaseActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("PickupActor")));
	ADrinkingPlaceActor* WaterSource = Cast<ADrinkingPlaceActor>(Actor);

	if(WaterSource)
	{


	}
	else if(Cart)
	{
		Cart->FreePickupSpot(Settler);
	}
	else if(Building)
	{
		
	}*/
	ACartBaseActor* Cart = Cast<ACartBaseActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("PickupActor")));
	if(Cart)
	{
		Cart->FreePickupSpot(Settler);
	}

		OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("PickupComponent"));
		OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("PickupLocation"));
		OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("PickupActor"));
	
		return EBTNodeResult::Failed;

	
}
