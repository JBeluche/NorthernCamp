// Copyright Creating Mountains!


#include "NorthernCamp/AIController/BehaviorTree/BTServices/BTS_UpdateWaterLocation.h"

#include "EngineUtils.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NorthernCamp/Actors/CartBaseActor.h"
#include "NorthernCamp/Actors/DrinkingPlaceActor.h"
#include "NorthernCamp/AIController/AISettlerController.h"

UBTS_UpdateWaterLocation::UBTS_UpdateWaterLocation()
{
	NodeName = "Update Water Actor and Location";
}

void UBTS_UpdateWaterLocation::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) 
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAISettlerController* Controller = Cast<AAISettlerController>(OwnerComp.GetAIOwner());
	ACharacterSettler* Settler = Cast<ACharacterSettler>(Controller->GetPawn());
	AActor* ClosestActorWithWater = nullptr;
	
	NavigationSystemv1 = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	
	if(NavigationSystemv1)
	{
		if(Controller != nullptr || Settler != nullptr)
		{
			float NewPathLength;
			float OldPathLength;
			
			//Check closest water source
			for (TActorIterator<ADrinkingPlaceActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
			{
				NavigationSystemv1->GetPathLength(Settler->GetActorLocation(), ActorItr->GetActorLocation(), NewPathLength);

				if(ClosestActorWithWater == nullptr)
				{
					ClosestActorWithWater = *ActorItr;
				}
				else if(NewPathLength < OldPathLength)
				{
					ClosestActorWithWater = *ActorItr;
				}
				OldPathLength = NewPathLength;
			}

			//Check any carts for water
			for (TActorIterator<ACartBaseActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
			{

				NavigationSystemv1->GetPathLength(Settler->GetActorLocation(), ActorItr->GetActorLocation(), NewPathLength);
				
				if(ClosestActorWithWater == nullptr && ActorItr->CheckResourceAvailability(EResourceType::Water, 1))
				{
					ClosestActorWithWater = *ActorItr;
				}
				else if(NewPathLength < OldPathLength  && ActorItr->CheckResourceAvailability(EResourceType::Water, 1))
				{
					ClosestActorWithWater = *ActorItr;
				}
				OldPathLength = NewPathLength;
			}

			//Check buildings for water
			for (TActorIterator<ABuildingBaseActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
			{
				NavigationSystemv1->GetPathLength(Settler->GetActorLocation(), ActorItr->GetActorLocation(), NewPathLength);

				if(ClosestActorWithWater == nullptr  && ActorItr->CheckResourceAvailability(EResourceType::Water, 1))
				{
					ClosestActorWithWater = *ActorItr;
				}
				else if(NewPathLength < OldPathLength  && ActorItr->CheckResourceAvailability(EResourceType::Water, 1))
				{
					ClosestActorWithWater = *ActorItr;
				}
				OldPathLength = NewPathLength;
			}

		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Casting failed in BTS_UpdateWaterLocation"), *Settler->GetName());
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("A settler is not finding the navigation system"));
	}

	if(ClosestActorWithWater)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("PickupActor"), ClosestActorWithWater);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("bResourceStillAvailable"), true);

		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), ClosestActorWithWater->GetActorLocation());
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("bResourceStillAvailable"), false);
	}

}
