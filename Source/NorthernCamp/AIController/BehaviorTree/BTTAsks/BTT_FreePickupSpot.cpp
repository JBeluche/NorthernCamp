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
	AActor* Actor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("PickupActor")));

	//Get the component
	if(Actor)
	{
		UResourceManagerComponent* ResourceManagerComp = Cast<UResourceManagerComponent>(Actor->GetComponentByClass(UResourceManagerComponent::StaticClass()));
		if(ResourceManagerComp)
		{
			ResourceManagerComp->FreePickupSpot(Settler);
		}
	}
	
	UE_LOG(LogTemp, Error,	TEXT("Firing freepickup"));
	
	OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("PickupComponent"));
	OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("PickupLocation"));
	OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("PickupActor"));

	return EBTNodeResult::Failed;

	
}
