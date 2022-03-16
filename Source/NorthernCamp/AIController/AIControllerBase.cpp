// Copyright Creating Mountains!


#include "NorthernCamp/AIController/AIControllerBase.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NorthernCamp/Characters/CharacterSettler.h"

AAIControllerBase::AAIControllerBase()
{

	

}

void AAIControllerBase::BeginPlay()
{
	CharacterOwner = Cast<ACharacterBase>(GetPawn());

	if(!CharacterOwner){ 	UE_LOG(LogTemp, Error, TEXT("AAIControllerBase: Nullptr, CharacterOwner")); return;}
	
	if(CharacterOwner->CurrentStance == ECurrentStance::Settler){
		FString Path =  "/Game/Blueprints/AI/BT_Settlers";
		CurrentBehaviorTree = Cast<UBehaviorTree>(StaticLoadObject(UBehaviorTree::StaticClass(), nullptr, *Path));
	}
	else if(CharacterOwner->CurrentStance == ECurrentStance::Defending)
	{
		FString Path =  "/Game/Blueprints/AI/BT_Defender";
		CurrentBehaviorTree = Cast<UBehaviorTree>(StaticLoadObject(UBehaviorTree::StaticClass(), nullptr, *Path));
	}
	else if(CharacterOwner->CurrentStance == ECurrentStance::Attacking)
	{
		FString Path = "/Game/Blueprints/AI/BT_Agresor";
		CurrentBehaviorTree = Cast<UBehaviorTree>(StaticLoadObject(UBehaviorTree::StaticClass(), nullptr, *Path));
	}




	
	if(CurrentBehaviorTree != nullptr)
	{
		RunBehaviorTree(CurrentBehaviorTree);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AAIControllerBase: Nullptr BehaviorTree") );
	}
}
