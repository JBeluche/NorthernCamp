// Copyright Creating Mountains!


#include "NorthernCamp/AIController/BehaviorTree/BTTAsks/BTT_Drink.h"

#include "AIController.h"
#include "EngineUtils.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NorthernCamp/Actors/BuildingBaseActor.h"
#include "NorthernCamp/Actors/CartBaseActor.h"
#include "NorthernCamp/Actors/DrinkingPlaceActor.h"
#include "NorthernCamp/AIController/AISettlerController.h"
#include "NorthernCamp/Characters/CharacterSettler.h"


UBTT_Drink::UBTT_Drink()
{
	NodeName = TEXT("Set Closest Water Location || Drink");
}

EBTNodeResult::Type UBTT_Drink::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);


	return EBTNodeResult::Failed;
}




/*
	
	//I have set this up to make sure the task does not iterate all to fast
	if(OwnerComp.GetBlackboardComponent()->GetValueAsFloat(TEXT("WaterTimerCheck")) < 1.0f)
	{
		float Value = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(TEXT("WaterTimerCheck")) + 0.1f;
		
		OwnerComp.GetBlackboardComponent()->SetValueAsFloat(TEXT("WaterTimerCheck"), Value);
	}
	else
	{
		ACharacterBase* Character = Cast<ACharacterBase>(OwnerComp.GetAIOwner()->GetPawn());
    	ACharacterSettler* Settler  = Cast<ACharacterSettler>(Character);

		OwnerComp.GetBlackboardComponent()->SetValueAsFloat(TEXT("WaterTimerCheck"), 0.0f);

		//Get nearest location with water
		AActor* ActorWithWater = GetClosestActorWithWater(OwnerComp);

		if(ActorWithWater)
		{
			UE_LOG(LogTemp, Error, TEXT("Settler: %s | Found actor with water"), *Settler->GetName());
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("WaterSourceLocation"), ActorWithWater->GetActorLocation());
		}
		
	
		
		if(ActorWithWater != nullptr && Settler != nullptr)
		{
			if(Character->WithinActionRadius(ActorWithWater))
			{
				UE_LOG(LogTemp, Error, TEXT("Settler: %s | Is within radius"), *Settler->GetName());
				bool Drank = GetWaterFromActor(ActorWithWater);
				if(Drank)
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("bIsThirsty"), false);
					Settler->Drink();
					return EBTNodeResult::Succeeded;
				}
			}
		}

	}
	
	return EBTNodeResult::Failed;

}

AActor* UBTT_Drink::GetClosestActorWithWater(UBehaviorTreeComponent& OwnerComp)
{
	AAISettlerController* Controller = Cast<AAISettlerController>(OwnerComp.GetAIOwner());
	ACharacterSettler* Settler = Cast<ACharacterSettler>(Controller->GetPawn());
	AActor* ClosestActorWithWater = nullptr;
	
	NavigationSystemv1 = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	
	if(NavigationSystemv1)
	{
		if(Controller != nullptr && Settler != nullptr)
		{
			float NewPathLength;
			float OldPathLength;
			
			//Check closest water source
			for (TActorIterator<ADrinkingPlaceActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
			{
			
				
				NavigationSystemv1->GetPathLength(Settler->GetActorLocation(), ActorItr->GetActorLocation(), NewPathLength);
				if(ClosestActorWithWater == nullptr)
				{
					ClosestActorWithWater = Cast<AActor>(*ActorItr);
				}
				else if(NewPathLength < OldPathLength)
				{
					ClosestActorWithWater = Cast<AActor>(*ActorItr);
				}
				OldPathLength = NewPathLength;
			}

			

			//Check any carts for water
			for (TActorIterator<ACartBaseActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
			{
				NavigationSystemv1->GetPathLength(Settler->GetActorLocation(), ActorItr->GetActorLocation(), NewPathLength);
				if(ClosestActorWithWater == nullptr && ActorItr->CheckResourceAvailability(EResourceType::Water, 1))
				{
					ClosestActorWithWater = Cast<AActor>(*ActorItr);
				}
				else if(NewPathLength < OldPathLength  && ActorItr->CheckResourceAvailability(EResourceType::Water, 1))
				{
					ClosestActorWithWater = Cast<AActor>(*ActorItr);
				}
				OldPathLength = NewPathLength;
			}

			//Check buildings for water
			for (TActorIterator<ABuildingBaseActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
			{
				NavigationSystemv1->GetPathLength(Settler->GetActorLocation(), ActorItr->GetActorLocation(), NewPathLength);
				if(ClosestActorWithWater == nullptr  && ActorItr->CheckResourceAvailability(EResourceType::Water, 1))
				{
					ClosestActorWithWater = Cast<AActor>(*ActorItr);
				}
				else if(NewPathLength < OldPathLength  && ActorItr->CheckResourceAvailability(EResourceType::Water, 1))
				{
					ClosestActorWithWater = Cast<AActor>(*ActorItr);
				}
				OldPathLength = NewPathLength;
			}

		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Settler: %s | Not finding the navigation system"), *Settler->GetName());
	}
	

	return ClosestActorWithWater;

}


bool UBTT_Drink::GetWaterFromActor(AActor* ActorWithWater)
{
	//Cast all three diferent actors
	ADrinkingPlaceActor* DrinkingPlace = Cast<ADrinkingPlaceActor>(ActorWithWater);
	ACartBaseActor* Cart = Cast<ACartBaseActor>(ActorWithWater);
	ABuildingBaseActor* Building = Cast<ABuildingBaseActor>(ActorWithWater);
	
	bool DrankSuccefully = false;
	
	if(DrinkingPlace)
	{
		DrankSuccefully = DrinkingPlace->Drink();
	}
	else if(Cart)
	{
		DrankSuccefully = Cart->ExtractRersouce(EResourceType::Water, 1);
	}
	else if(Building)
	{
		DrankSuccefully = Building->ExtractRersouce(EResourceType::Water, 1);
	}

	return DrankSuccefully;
}

*/





