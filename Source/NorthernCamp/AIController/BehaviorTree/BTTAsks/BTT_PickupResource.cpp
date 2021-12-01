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
	UResourcesPickupSpot* PickupSpot = Cast<UResourcesPickupSpot>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("PickupComponent")));
	AActor* Actor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("PickupActor")));

	

	bool PickedResource = false;

	if(PickupSpot && Actor)
	{
		AAISettlerController* Controller = Cast<AAISettlerController>(OwnerComp.GetAIOwner());
		ACharacterSettler* Settler = Cast<ACharacterSettler>(Controller->GetPawn());
		ACharacter* Character = Cast<ACharacter>(Controller->GetPawn());

		UResourceManagerComponent* ResourceManagerComp = Cast<UResourceManagerComponent>(Actor->GetComponentByClass(UResourceManagerComponent::StaticClass()));

		
		if(ResourceManagerComp)
		{
			PickedResource = ResourceManagerComp->ExtractRersouce(Settler->ResourceManagerComp->GetResourceNeed().ResourceType, Settler->ResourceManagerComp->GetResourceNeed().Amount, Character);
		}

		if(PickedResource)
		{

			//Add to settlers hand
			Settler->PutResourceInHand(Settler->ResourceManagerComp->GetResourceNeed().ResourceType, Settler->ResourceManagerComp->GetResourceNeed().Amount);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("bHasWaterInHand"), true);
			
			return EBTNodeResult::Succeeded;
		}
		

	}

	return EBTNodeResult::Failed;
}
