// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_Attack.generated.h"

class ACharacterBase;
/**
 * 
 */
UCLASS()
class NORTHERNCAMP_API UBTT_Attack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTT_Attack();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	FTimerHandle TimerHandleAttack;
	FTimerDelegate TimerDelegateAttack;
	bool bAttackCompleted = false;

	void ApplyDamage();

	ACharacterBase* Character;
	ACharacterBase* EnemyTarget;
	
};
