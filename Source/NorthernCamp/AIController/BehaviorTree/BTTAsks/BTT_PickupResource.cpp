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
	AActor* ActorWithResource = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("ActorWithResource")));


	if(ActorWithResource)
	{
		AAISettlerController* Controller = Cast<AAISettlerController>(OwnerComp.GetAIOwner());
		ACharacterSettler* Settler = Cast<ACharacterSettler>(Controller->GetPawn());
		ACharacter* Character = Cast<ACharacter>(Controller->GetPawn());

		UResourceManagerComponent* ResourceManagerComp = Cast<UResourceManagerComponent>(ActorWithResource->GetComponentByClass(UResourceManagerComponent::StaticClass()));

		
		if(ResourceManagerComp && Character)
		{
			if(Settler->ResourceManagerComp->GetCurrentResoucesToFetch().ResourceType == EResourceType::None)
			{
				UE_LOG(LogTemp, Error, TEXT("UBTT_PickupResource: I want to extract a resource but cannot find my priority need"));
				return EBTNodeResult::Failed;
			}
			
			bool bResourceAvailable = ResourceManagerComp->CheckResourceAvailability(Settler->ResourceManagerComp->GetCurrentResoucesToFetch());
			if(bResourceAvailable)
			{
				bool bTransferSuccesfull = ResourceManagerComp->TransferResources(Settler->ResourceManagerComp->GetCurrentResoucesToFetch(), Settler->ResourceManagerComp);

				if(bTransferSuccesfull)
				{
					UE_LOG(LogTemp, Error, TEXT("UBTT_PickupResource: Transfer succesfull"));

					return EBTNodeResult::Succeeded;
				}
			}
			}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("UBTT_PickupResource: Nullpt ResourceManagerComp && Character "));
			return EBTNodeResult::Failed;
		}
	}

	return EBTNodeResult::Failed;
}
