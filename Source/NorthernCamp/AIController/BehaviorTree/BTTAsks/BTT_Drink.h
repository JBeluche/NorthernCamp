// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_Drink.generated.h"

/**
 * 
 */
UCLASS()
class NORTHERNCAMP_API UBTT_Drink : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTT_Drink();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	AActor* GetClosestActorWithWater(UBehaviorTreeComponent& OwnerComp);
	bool GetWaterFromActor(AActor* ActorWithWater);

	UPROPERTY()
	UNavigationSystemV1* NavigationSystemv1;

};
