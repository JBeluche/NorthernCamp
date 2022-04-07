// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "NorthernCamp/Controllers/DayNightActorController.h"
#include "NorthernCamp/Characters/CharacterBase.h"
#include "Perception/AISenseConfig_Sight.h"

#include "AIControllerBase.generated.h"


enum class ECurrentStance : uint8;
class ACharacterBase;


UCLASS()
class NORTHERNCAMP_API AAIControllerBase : public AAIController
{
	GENERATED_BODY()

public:
	AAIControllerBase();

	virtual void BeginPlay() override;
	void SetupController();
	void SetBehaviorTree(ECurrentStance NewStance);
	void SetCharacterIsFrozen(bool bIsFrozen);

	ACharacterBase* CharacterOwner;

	UBehaviorTree* CurrentBehaviorTree;

	TSubclassOf<class UBehaviorTree> BehaviorTreeSettler;
	TSubclassOf<class UBehaviorTree> BehaviorTreeDefender;
	TSubclassOf<class UBehaviorTree> BehaviorTreeAgresor;

	UAISenseConfig_Sight* SightConfig;


	
private:
	
	UFUNCTION()
	void PerceptionUpdated(TArray<AActor*> const& updated_actors);

	void SetupPerceptionSystem();

};

