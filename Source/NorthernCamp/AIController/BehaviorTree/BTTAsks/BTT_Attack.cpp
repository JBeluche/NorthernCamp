// Copyright Creating Mountains!


#include "NorthernCamp/AIController/BehaviorTree/BTTAsks/BTT_Attack.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "NorthernCamp/AIController/AIControllerBase.h"
#include "NorthernCamp/AIController/BehaviorTree/BlackboardKeys/AgresorBlackboardKeys.h"
#include "NorthernCamp/Characters/CharacterBase.h"
#include "NorthernCamp/Characters/Components/VitalsComponentBase.h"


UBTT_Attack::UBTT_Attack()
{
	NodeName = TEXT("Attack Ennemy Target");
}

EBTNodeResult::Type UBTT_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Play animation
	//If at the end of animation, the enemy is still in range. Remove health from enemy
		
	Character = Cast<ACharacterBase>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("SelfActor")));
	EnemyTarget = Cast<ACharacterBase>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AgresorBlackboardKeys::EnnemyTarget));
	
	UAnimMontage* AttackAnimation = Character->GetAttackAnimation();
	if(!AttackAnimation){UE_LOG(LogTemp, Error, TEXT("UBTT_Attack::ExecuteTask nullptr AttackAnimation"));}
	
	Character->PlayAnimationMontage(AttackAnimation, false);
	
//	UE_LOG(LogTemp, Error, TEXT("Character: %s, attacked: %s"), *Character->GetName(), *EnemyTarget->GetName());
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(AgresorBlackboardKeys::AttackDuration, AttackAnimation->GetPlayLength());

	return EBTNodeResult::Succeeded;

}

