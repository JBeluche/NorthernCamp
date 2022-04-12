// Copyright Creating Mountains!


#include "NorthernCamp/AIController/BehaviorTree/BTServices/BTS_UpdateEnemyTarget.h"

#include "EngineUtils.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NorthernCamp/AIController/AIControllerBase.h"
#include "NorthernCamp/AIController/BehaviorTree/BlackboardKeys/AgresorBlackboardKeys.h"
#include "NorthernCamp/Characters/CharacterBase.h"
#include "NorthernCamp/Characters/CharacterHero.h"
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
	ACharacterBase* NearestEnemy = nullptr;
	ACharacterBase* OldNearestEnemy = Cast<ACharacterBase>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AgresorBlackboardKeys::EnnemyTarget));


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
			
				if (NearestDistance > TempDistance && !PercievedCharacter->bDiedOrWounded) 
				{
					NearestDistance = TempDistance; 
					NearestEnemy = PercievedCharacter; 
				} 
			}
		}
	}
	
	//Set closest enemy
	if(NearestEnemy != nullptr)
	{
		if(NearestEnemy != OldNearestEnemy)
		{
			
			//UE_LOG(LogTemp, Error, TEXT("Character: %s, setting character: %s as target"), *Character->GetName(), *NearestEnemy->GetName());

			OwnerComp.GetBlackboardComponent()->ClearValue(AgresorBlackboardKeys::EnnemyTarget);
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), NearestEnemy);
		}
		

	}
	else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(AgresorBlackboardKeys::EnnemyTarget);
	}


}