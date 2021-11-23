// Copyright Creating Mountains!


#include "NorthernCamp/AIController/AISettlerController.h"

#include "EngineUtils.h"
#include "NavigationSystem.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "NorthernCamp/Actors/BuildingBaseActor.h"
#include "NorthernCamp/Actors/CartBaseActor.h"
#include "NorthernCamp/Actors/DrinkingPlaceActor.h"
#include "NorthernCamp/CharacterComponents/VitalsComponent.h"


AAISettlerController::AAISettlerController()
{

}


void AAISettlerController::BeginPlay()
{
	Super::BeginPlay();


	CharacterOwner = Cast<ACharacterSettler>(GetCharacter());
	/*if(CharacterOwner)
	{
		CharacterOwner->GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AAISettlerController::OnOverlapBegin);
	}*/

	
	if(BehaviorTree != nullptr)
	{
		RunBehaviorTree(BehaviorTree);
		GetBlackboardComponent()->SetValueAsFloat(TEXT("WaterTimerCheck"), 1.1f);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No behavior tree set") );
	}
	NavigationSystemv1 = Cast<UNavigationSystemV1>(UNavigationSystemV1::GetCurrent(GetWorld()));
	CharacterOwner = Cast<ACharacterSettler>(GetPawn());


	//Check if you can find the DayNightActorController
	for (TActorIterator<ADayNightActorController> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		DayNightActorController = Cast<ADayNightActorController>(*ActorItr);
	}

	if(DayNightActorController)
	{
		DayNightActorController->AnHourStruck.AddDynamic(this, &AAISettlerController::HourStruck);
	}
	
	CurrentTimerManager = &GetWorld()->GetTimerManager();
}

void AAISettlerController::HourStruck(float CurrentHour)
{
	
	//Check objectives


 
}

//Check objectives

void AAISettlerController::WaterIsLow()
{
	//Check if you already can drink(near building, or cart) Else setup a timer to check where to go to find water.
	/*TArray< AActor * >  OverlappingActors;
	TSubclassOf< AActor > ClassFilter;
	bool FoundWater = false;

	GetOverlappingActors(OverlappingActors, ClassFilter);
	for (int i = 0; i < OverlappingActors.Num(); i++) { 
		if(FoundWater){return;}
		
		ABuildingBaseActor* Building = Cast<ABuildingBaseActor>(OverlappingActors[i]);
		ACartBaseActor* Cart = Cast<ACartBaseActor>(OverlappingActors[i]);
		if(Building)
		{
			FoundWater = Building->CheckOrRetrieveResource(EResourceType::Water, 1, false);
		
		}
		else if(Cart && !FoundWater)
		{
			FoundWater = Cart->CheckOrRetrieveResource(EResourceType::Water, 1, false);
		}
		
	}
	if(FoundWater)
	{
		UE_LOG(LogTemp, Error, TEXT("I found my water, and was already overlapping"));

	}
	else
	{*/
		GetBlackboardComponent()->SetValueAsBool(TEXT("bIsThirsty"), true);
		
		/*FTimerDelegate TimerDel;
	 
		TimerDel.BindUFunction(this, FName("GetClosestStockedResourceLocation"), EResourceType::Water, 1);
		GetWorld()->GetTimerManager().SetTimer(TodoAtBuildingTimerHandle, TimerDel, 1.0f, true);*/
	//}

		
}



void AAISettlerController::GetClosestStockedResourceLocation(UEnum* ResourceType, int32 AmountNeeded)
{
/*
//	GetBlackboardComponent()->SetValueAsVector(TEXT("WaterSourceLocation"), GetClosestStockedResourceLocation());
	
	NavigationSystemv1 = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	
		if(CharacterOwner == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Cant get character") );
			return;
		}
		float NewPathLength;
		float OldPathLength;
		bool FirstWaterSourceChecked = false;

		//float ClosestBuildingWithWaterDistance;
		float ClosestCartWithWaterDistance;
		float ClosestWaterSourceDistance;

		//ADrinkingPlaceActor* ClosestWaterSource = nullptr;
		ACartBaseActor* ClosestCartWithWater = nullptr;
		ABuildingBaseActor* ClosestBuildingWithWater = nullptr;

		//Check closest water source
		for (TActorIterator<ADrinkingPlaceActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			NavigationSystemv1->GetPathLength(CharacterOwner->GetActorLocation(), ActorItr->GetActorLocation(), NewPathLength);
			if(FirstWaterSourceChecked == false)
			{
				FirstWaterSourceChecked = true;
				GetBlackboardComponent()->SetValueAsVector(TEXT("WaterSourceLocation"), ActorItr->GetActorLocation());
			}
			else if(NewPathLength < OldPathLength)
			{
				GetBlackboardComponent()->SetValueAsVector(TEXT("WaterSourceLocation"), ActorItr->GetActorLocation());
			}
			UE_LOG(LogTemp, Error, TEXT("Setting water source to water source locatin: %s"));
			
			OldPathLength = NewPathLength;
			ClosestWaterSourceDistance = NewPathLength;

		}

		//Check any carts for water
		for (TActorIterator<ACartBaseActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			NavigationSystemv1->GetPathLength(CharacterOwner->GetActorLocation(), ActorItr->GetActorLocation(), NewPathLength);
			if(NewPathLength < OldPathLength && NewPathLength < ClosestWaterSourceDistance)
			{
				ACartBaseActor* Cart = Cast<ACartBaseActor>(*ActorItr);
				if(Cart->CheckResourceAvailability(EResourceType::Water, 1))
				{
					const float TempDistance = FVector::Dist(CharacterOwner->GetActorLocation(), Cart->GetActorLocation());
					if(TempDistance < CharacterOwner->ActionRange)
					{
						bool DrinkedWater = Cart->ExtractRersouce(EResourceType::Water, 1);
						if(DrinkedWater){GetBlackboardComponent()->SetValueAsBool(TEXT("bIsThirsty"), false);}
						
					}
					NavigationSystemv1->GetPathLength(CharacterOwner->GetActorLocation(), Cart->GetActorLocation(), ClosestCartWithWaterDistance);
					GetBlackboardComponent()->SetValueAsVector(TEXT("WaterSourceLocation"), Cart->GetActorLocation());
					ClosestCartWithWater = Cast<ACartBaseActor>(*ActorItr);
				}
			}
			OldPathLength = NewPathLength;
		}

		//Check buildings for water
		for (TActorIterator<ABuildingBaseActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			NavigationSystemv1->GetPathLength(CharacterOwner->GetActorLocation(), ActorItr->GetActorLocation(), NewPathLength);
			if(NewPathLength < OldPathLength && NewPathLength < ClosestWaterSourceDistance && NewPathLength < ClosestCartWithWaterDistance)
			{
				ABuildingBaseActor* Building = Cast<ABuildingBaseActor>(*ActorItr);
				if(Building->CheckOrRetrieveResource(EResourceType::Water, 1, true))
				{
					NavigationSystemv1->GetPathLength(CharacterOwner->GetActorLocation(), Building->GetActorLocation(), ClosestCartWithWaterDistance);
					GetBlackboardComponent()->SetValueAsVector(TEXT("WaterSourceLocation"), Building->GetActorLocation());
					ClosestBuildingWithWater = Cast<ABuildingBaseActor>(*ActorItr);

					UE_LOG(LogTemp, Error, TEXT("I check everything and this is the closest: %s"));
				}
			}
			OldPathLength = NewPathLength;
		}
	
	

	*/

}

/*
void AAISettlerController::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	//If thirsty, go drink
	ABuildingBaseActor* Building = Cast<ABuildingBaseActor>(OtherActor);
	ACartBaseActor* Cart = Cast<ACartBaseActor>(OtherActor);
	bool FoundWater = false;
	if(Building)
	{
		FoundWater = Building->CheckOrRetrieveResource(EResourceType::Water, 1, false);
	}
	if(Cart && FoundWater == false)
	{
		FoundWater = Cart->ExtractRersouce(EResourceType::Water, 1);
	}
	if(FoundWater)
	{
		UE_LOG(LogTemp, Error, TEXT("I found my water and reset my stats"));
		//Get Vitals
		//CharacterOwner->VitalsComponent->CurrentWaterMeter = CharacterOwner->VitalsComponent->InitialWaterMeter;
		GetBlackboardComponent()->SetValueAsBool(TEXT("bIsThirsty"), false);
	}

}

void AAISettlerController::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	

}*/
/*
void AAISettlerController::CheckTodoAtBuilding()
{

	//If thirsty
	if(GetBlackboardComponent()->GetValueAsBool(TEXT("bIsWaterLow")))
	{
		bool Drank = OverlappingBuilding->RetrieveResource(EResourceType::Water, 1);
			
		if(Drank)
		{
			//Get Vitals
			CharacterOwner->VitalsComponent->CurrentWaterMeter = CharacterOwner->VitalsComponent->InitialWaterMeter;
			GetBlackboardComponent()->SetValueAsBool(TEXT("bIsWaterLow"), false);

			//Trigger animation and duration. 
			

			return;
		}
	}
	
}

void AAISettlerController::SettlerIsBusy(Animation type bool ShouldFreeze, float Duration)
{
	//Pause the building timer.
	
	if(ShouldFreeze)
	{
		GetBlackboardComponent()->SetValueAsBool(TEXT("bIsFrozen"), true);
		CurrentTimerManager().SetTimer(CharacterFrozenTimerHandle, this, &AAISettlerController::UnFreeze, Duration, false);
	}

	//Have timer? before triggering the overlap event again?

	
}

void AAISettlerController::UnFreeze()
{
	//GetBlackboardComponent()->SetValueAsBool(TEXT("bIsFrozen"), false);
}*/