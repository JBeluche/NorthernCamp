// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "NorthernCamp/Controllers/DayNightActorController.h"

#include "AIControllerBase.generated.h"


class ACharacterBase;


UCLASS()
class NORTHERNCAMP_API AAIControllerBase : public AAIController
{
	GENERATED_BODY()

public:
	AAIControllerBase();

	virtual void BeginPlay() override;
	
	ACharacterBase* CharacterOwner;

	UBehaviorTree* CurrentBehaviorTree;

	TSubclassOf<class UBehaviorTree> BehaviorTreeSettler;
	TSubclassOf<class UBehaviorTree> BehaviorTreeDefender;
	TSubclassOf<class UBehaviorTree> BehaviorTreeAgresor;
	

	
};
