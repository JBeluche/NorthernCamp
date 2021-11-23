// Copyright Creating Mountains!


#include "NorthernCamp/AIController/BehaviorTree/BTServices/BTS_UpdateWaterLocation.h"

#include "EngineUtils.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NorthernCamp/Actors/CartBaseActor.h"
#include "NorthernCamp/Actors/DrinkingPlaceActor.h"
#include "NorthernCamp/AIController/AISettlerController.h"

UBTS_UpdateWaterLocation::UBTS_UpdateWaterLocation()
{
	NodeName = "Update Water Location";
}

void UBTS_UpdateWaterLocation::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) 
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAISettlerController* Controller = Cast<AAISettlerController>(OwnerComp.GetAIOwner());
	ACharacterSettler* Settler = Cast<ACharacterSettler>(Controller->GetPawn());
	FVector ClosestWaterLocation;
	bool FoundWater = false;
	
	NavigationSystemv1 = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	
	if(NavigationSystemv1)
	{
		if(Controller != nullptr && Settler != nullptr)
		{
			float NewPathLength;
			float OldPathLength = NULL;
			
			//Check closest water source
			for (TActorIterator<ADrinkingPlaceActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
			{
								
				NavigationSystemv1->GetPathLength(Settler->GetActorLocation(), ActorItr->GetActorLocation(), NewPathLength);
				if(OldPathLength == NULL){OldPathLength = NewPathLength;}

				if(FoundWater == false)
				{
					FoundWater = true;
					ClosestWaterLocation = ActorItr->GetActorLocation();
				}
				else if(NewPathLength < OldPathLength)
				{
					FoundWater = true;
					ClosestWaterLocation = ActorItr->GetActorLocation();
				}
				OldPathLength = NewPathLength;
			}

			//Check any carts for water
			for (TActorIterator<ACartBaseActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
			{
				NavigationSystemv1->GetPathLength(Settler->GetActorLocation(), ActorItr->GetActorLocation(), NewPathLength);
				
				if(OldPathLength == NULL){OldPathLength = NewPathLength;}

				if(FoundWater == false && ActorItr->CheckResourceAvailability(EResourceType::Water, 1))
				{
					FoundWater = true;
					ClosestWaterLocation = ActorItr->GetActorLocation();
				}
				else if(NewPathLength < OldPathLength  && ActorItr->CheckResourceAvailability(EResourceType::Water, 1))
				{
					FoundWater = true;
					ClosestWaterLocation = ActorItr->GetActorLocation();
				}
				OldPathLength = NewPathLength;
			}

			//Check buildings for water
			for (TActorIterator<ABuildingBaseActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
			{
				NavigationSystemv1->GetPathLength(Settler->GetActorLocation(), ActorItr->GetActorLocation(), NewPathLength);
				if(OldPathLength == NULL){OldPathLength = NewPathLength;}

				if(FoundWater == false  && ActorItr->CheckResourceAvailability(EResourceType::Water, 1))
				{
					FoundWater = true;
					ClosestWaterLocation = ActorItr->GetActorLocation();
				}
				else if(NewPathLength < OldPathLength  && ActorItr->CheckResourceAvailability(EResourceType::Water, 1))
				{
					FoundWater = true;
					ClosestWaterLocation = ActorItr->GetActorLocation();
				}
				OldPathLength = NewPathLength;
			}

		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Settler: %s | Not finding the navigation system"), *Settler->GetName());
	}

	if(FoundWater)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), ClosestWaterLocation);
	}

}
