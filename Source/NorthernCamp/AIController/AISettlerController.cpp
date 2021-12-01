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
	
	
}

void AAISettlerController::HourStruck(float CurrentHour)
{
	
	//Check objectives


 
}

void AAISettlerController::WaterIsLow()
{
	CharacterOwner->ResourceManagerComp->AddResourceNeed(EResourceType::Water, 1);
	GetBlackboardComponent()->SetValueAsBool(TEXT("bIsThirsty"), true);
}


