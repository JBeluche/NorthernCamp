// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_ResetFocus.generated.h"

/**
 * 
 */
UCLASS()
class NORTHERNCAMP_API UBTT_ResetFocus : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTT_ResetFocus();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
