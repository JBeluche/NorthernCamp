// Copyright Creating Mountains!


#include "NorthernCamp/AIController/BehaviorTree/BTTAsks/BTT_PickupResource.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Components/BoxComponent.h"
#include "NorthernCamp/Actors/BuildingBaseActor.h"
#include "NorthernCamp/Actors/CartBaseActor.h"
#include "NorthernCamp/Actors/DrinkingPlaceActor.h"
#include "NorthernCamp/AIController/AISettlerController.h"


UBTT_PickupResource::UBTT_PickupResource()
{
	NodeName = TEXT("Try and pickup resource");
}

EBTNodeResult::Type UBTT_PickupResource::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	//Cast the box component
	UBoxComponent* BoxComponent = Cast<UBoxComponent>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("PickupComponent")));

	bool PickedResource = false;

	if(BoxComponent)
	{
		AAISettlerController* Controller = Cast<AAISettlerController>(OwnerComp.GetAIOwner());
		ACharacterSettler* Settler = Cast<ACharacterSettler>(Controller->GetPawn());
		
		//Cast to cart, building, watersource
		ABuildingBaseActor* Building = Cast<ABuildingBaseActor>(BoxComponent->GetOwner());
		ACartBaseActor* Cart = Cast<ACartBaseActor>(BoxComponent->GetOwner());
		ADrinkingPlaceActor* WaterSource = Cast<ADrinkingPlaceActor>(BoxComponent->GetOwner());

		if(WaterSource)
		{
			PickedResource = WaterSource->PickupWater();
		}
		else if(Cart)
		{
			PickedResource = Cart->ExtractRersouce(EResourceType::Water, 1);
			
		}
		else if (Building)
		{
			PickedResource = Building->ExtractRersouce(EResourceType::Water, 1);
		}

		if(PickedResource)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s: took water"), *Controller->GetPawn()->GetName());

			//Add to settlers hand
			Settler->PutResourceInHand(EResourceType::Water, 1);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("bHasWaterInHand"), true);
			
			return EBTNodeResult::Succeeded;
		}
		

	}

	return EBTNodeResult::Failed;
}
