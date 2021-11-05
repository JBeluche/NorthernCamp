// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "AIControllerBase.h"

#include "AISettlerController.generated.h"

/**
 * 
 */
UCLASS()
class NORTHERNCAMP_API AAISettlerController : public AAIControllerBase
{
	GENERATED_BODY()
	
	public:

	AAISettlerController();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBehaviorTree* BehaviorTree;
};


	
