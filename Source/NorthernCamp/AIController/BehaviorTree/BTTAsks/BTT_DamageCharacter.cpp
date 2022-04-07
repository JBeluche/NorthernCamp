// Copyright Creating Mountains!


#include "NorthernCamp/AIController/BehaviorTree/BTTAsks/BTT_DamageCharacter.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "NorthernCamp/AIController/BehaviorTree/BlackboardKeys/AgresorBlackboardKeys.h"
#include "NorthernCamp/Characters/CharacterBase.h"
#include "NorthernCamp/Characters/Components/VitalsComponentBase.h"

UBTT_DamageCharacter::UBTT_DamageCharacter()
{
	NodeName = TEXT("Damage Ennemy Target");
}

EBTNodeResult::Type UBTT_DamageCharacter::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	ACharacterBase* Character = Cast<ACharacterBase>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("SelfActor")));
	ACharacterBase* Enemy = Cast<ACharacterBase>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AgresorBlackboardKeys::EnnemyTarget));

	if(!Enemy){UE_LOG(LogTemp,Error, TEXT("UBTT_DamageCharacter::ExecuteTask nullptr EnemyTarget")); return EBTNodeResult::Failed;}
	if(!Character){UE_LOG(LogTemp,Error, TEXT("UBTT_DamageCharacter::ExecuteTask nullptr Character")); return EBTNodeResult::Failed;}
	if(!Enemy->GetVitals()){UE_LOG(LogTemp,Error, TEXT("UBTT_DamageCharacter::ExecuteTask nullptr Enemy->GetVitals()")); return EBTNodeResult::Failed;}

	const float TempDistance = FVector::Dist(Character->GetActorLocation(), Enemy->GetActorLocation());
	
	//Check if ennemy is still in range
	if(TempDistance < Character->GetAttackRange())
	{
		Enemy->GetVitals()->LoseHealth(Character->GetWeaponDamage());
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;

}