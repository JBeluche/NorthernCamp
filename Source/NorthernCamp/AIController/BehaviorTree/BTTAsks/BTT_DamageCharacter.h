// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_DamageCharacter.generated.h"

/**
 * 
 */
UCLASS()
class NORTHERNCAMP_API UBTT_DamageCharacter : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTT_DamageCharacter();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
