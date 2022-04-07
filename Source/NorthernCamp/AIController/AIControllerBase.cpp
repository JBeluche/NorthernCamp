// Copyright Creating Mountains!


#include "NorthernCamp/AIController/AIControllerBase.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NorthernCamp/Characters/CharacterSettler.h"
#include "Perception/AIPerceptionComponent.h"

AAIControllerBase::AAIControllerBase()
{
	SetupPerceptionSystem();

	
}

void AAIControllerBase::BeginPlay()
{
	Super::BeginPlay();
	

}

void AAIControllerBase::SetupPerceptionSystem()
{
	// create and initialise sight configuration object
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	if (SightConfig)
	{
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
		SightConfig->SightRadius = 25000.0f;
		SightConfig->LoseSightRadius = SightConfig->SightRadius + 250.0f;
		SightConfig->PeripheralVisionAngleDegrees = 360.0f;
		SightConfig->SetMaxAge(5.0f);
		//SightConfig->AutoSuccessRangeFromLastSeenLocation = 520.0f;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

		// add sight configuration component to perception component
		GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
		GetPerceptionComponent()->ConfigureSense(*SightConfig);
		GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AAIControllerBase::PerceptionUpdated);
	}
}

void AAIControllerBase::PerceptionUpdated(TArray<AActor*> const& updated_actors)
{
	
	//We dont use this anymore, not even the sight config. Maybe get rid of it.
	/*for (size_t x = 0; x < updated_actors.Num(); ++x)
	{

		ACharacterBase* DetectedCharacter = Cast<ACharacterBase>(updated_actors[x]);
	
	}*/
}


void AAIControllerBase::SetupController()
{
	CharacterOwner = Cast<ACharacterBase>(GetPawn());
	if(!CharacterOwner){ 	UE_LOG(LogTemp, Error, TEXT("AAIControllerBase::SetupController Nullptr, CharacterOwner")); return;}
	SetBehaviorTree(CharacterOwner->CurrentStance);
	
}

void AAIControllerBase::SetBehaviorTree(ECurrentStance NewStance)
{
	if(NewStance == ECurrentStance::Settler){
		FString Path =  "/Game/Blueprints/AI/BT_Settlers";
		CurrentBehaviorTree = Cast<UBehaviorTree>(StaticLoadObject(UBehaviorTree::StaticClass(), nullptr, *Path));
	}
	else if(NewStance == ECurrentStance::Defending)
	{
		FString Path =  "/Game/Blueprints/AI/BT_Defender";
		CurrentBehaviorTree = Cast<UBehaviorTree>(StaticLoadObject(UBehaviorTree::StaticClass(), nullptr, *Path));
	}
	else if(NewStance == ECurrentStance::Attacking)
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
		UE_LOG(LogTemp, Error, TEXT("AAIControllerBase::SetBehaviorTree Nullptr BehaviorTree") );
	}
	//Set self actor
	if(CurrentBehaviorTree != nullptr)
	{
		GetBlackboardComponent()->SetValueAsObject(TEXT("SelfActor"), CharacterOwner);
	}
}

void AAIControllerBase::SetCharacterIsFrozen(bool bIsFrozen)
{
	if(CurrentBehaviorTree != nullptr)
	{
		GetBlackboardComponent()->SetValueAsBool(TEXT("bIsFrozen"), bIsFrozen);
	}
}

