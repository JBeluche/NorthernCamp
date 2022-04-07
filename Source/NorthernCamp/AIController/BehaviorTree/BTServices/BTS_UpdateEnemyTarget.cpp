// Copyright Creating Mountains!


#include "NorthernCamp/AIController/BehaviorTree/BTServices/BTS_UpdateEnemyTarget.h"

#include "EngineUtils.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NorthernCamp/AIController/AIControllerBase.h"
#include "NorthernCamp/AIController/BehaviorTree/BlackboardKeys/AgresorBlackboardKeys.h"
#include "NorthernCamp/Characters/CharacterBase.h"
#include "Perception/AIPerceptionComponent.h"

UBTS_UpdateEnemyTarget::UBTS_UpdateEnemyTarget()
{
	NodeName = "Update Ennemy Target and Range";
}

void UBTS_UpdateEnemyTarget::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	//Get the perception and get the closest enemy

	ACharacterBase* Character = Cast<ACharacterBase>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("SelfActor")));
	AAIControllerBase* AIController = Cast<AAIControllerBase>(Character->GetController());
	TArray<AActor*> PercievedActors;
	AIController->PerceptionComponent->GetCurrentlyPerceivedActors( UAISense_Sight::StaticClass(), PercievedActors);
	ACharacterBase* NearestEnemy = nullptr; ;
	float NearestDistance = BIG_NUMBER;
	
	//Set the closest
	for (TActorIterator<ACharacterBase> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ACharacterBase* PercievedCharacter = Cast<ACharacterBase>(*ActorItr);
		if(PercievedCharacter != nullptr)
		{
			if(PercievedCharacter->Faction != Character->Faction)
			{
				FVector MyLocation = Character->GetActorLocation(); 
				FVector OtherPawnLocation = PercievedCharacter->GetActorLocation(); 
				const float TempDistance = FVector::Dist(MyLocation, OtherPawnLocation); 
				if (NearestDistance > TempDistance) 
				{
					//UE_LOG(LogTemp, Error, TEXT("Character: %s, found this character: %s to be closer"), *Character->GetName(), *PercievedCharacter->GetName());
					NearestDistance = TempDistance; 
					NearestEnemy = PercievedCharacter; 
				} 
			}
		}
	}
	

	/*
	for(AActor* Actor : PercievedActors)
	{
		UE_LOG(LogTemp, Error, TEXT("Character: %s, Percieved this character: %s"), *Character->GetName(), *Actor->GetName());


		ACharacterBase* PercievedCharacter = Cast<ACharacterBase>(Actor);
		if(PercievedCharacter != nullptr)
		{
			if(PercievedCharacter->Faction != Character->Faction)
			{
				FVector MyLocation = Character->GetActorLocation(); 
				FVector OtherPawnLocation = PercievedCharacter->GetActorLocation(); 
				const float TempDistance = FVector::Dist(MyLocation, OtherPawnLocation); 
				if (NearestDistance > TempDistance) 
				{
					UE_LOG(LogTemp, Error, TEXT("Character: %s, found this character: %s to be closer"), *Character->GetName(), *PercievedCharacter->GetName());
					NearestDistance = TempDistance; 
					NearestEnemy = PercievedCharacter; 
				} 
			}
		}
	}*/



	//Set closest enemy
	if(NearestEnemy != nullptr)
	{
		if(Character->GetAttackRange() > (Character->GetActorLocation() - NearestEnemy->GetActorLocation()).Size())
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(AgresorBlackboardKeys::bIsInRange, true);
		}
		else
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(AgresorBlackboardKeys::bIsInRange, false);

		}
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), NearestEnemy);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(AgresorBlackboardKeys::EnnemyTarget);
	}


}