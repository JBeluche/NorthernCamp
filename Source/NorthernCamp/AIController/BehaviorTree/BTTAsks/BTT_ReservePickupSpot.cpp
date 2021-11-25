// Copyright Creating Mountains!


#include "NorthernCamp/AIController/BehaviorTree/BTTAsks/BTT_ReservePickupSpot.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NorthernCamp/Actors/CartBaseActor.h"
#include "NorthernCamp/Actors/DrinkingPlaceActor.h"
#include "NorthernCamp/Characters/CharacterSettler.h"

UBTT_ReservePickupSpot::UBTT_ReservePickupSpot()
{
	NodeName = TEXT("Reserve pickup spot");
}

EBTNodeResult::Type UBTT_ReservePickupSpot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACharacterSettler* Settler  = Cast<ACharacterSettler>(OwnerComp.GetAIOwner()->GetPawn());
	
	AActor* Actor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("PickupActor")));
	
	//Cast to cart, building, watersource
	ABuildingBaseActor* Building = Cast<ABuildingBaseActor>(Actor);
	ACartBaseActor* Cart = Cast<ACartBaseActor>(Actor);
	ADrinkingPlaceActor* WaterSource = Cast<ADrinkingPlaceActor>(Actor);

	

	UBoxComponent* PickupComponent = nullptr;

	if(WaterSource)
	{


	}
	else if(Cart != nullptr)
	{
		PickupComponent = Cart->ReservePickupSpot(Settler);
	}
	else if(Building)
	{
		
	}
	
	if(PickupComponent != nullptr)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("PickupComponent"), PickupComponent);
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("PickupLocation"), PickupComponent->GetComponentLocation());
		return EBTNodeResult::Succeeded;
	}



	return EBTNodeResult::Failed;
}

