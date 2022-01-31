// Copyright Creating Mountains!


#include "NorthernCamp/Actors/CartBaseActor.h"

#include "Components/BoxComponent.h"
#include "NorthernCamp/Actors/BuildingBaseActor.h"
#include "NorthernCamp/Characters/CharacterSettler.h"

//////
// FEATURES IDEAS
//-Reserve resource for incoming settler



// Sets default values
ACartBaseActor::ACartBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);
	
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	MeshComp->SetupAttachment(SceneComponent);

	ResourceManagerComp = CreateDefaultSubobject<UResourceManagerComponent>(TEXT("Resource Manager"));
	
	
}

// Called when the game starts or when spawned
void ACartBaseActor::BeginPlay()
{
	Super::BeginPlay();
	
//	ResourceManagerComp->AddResource(EResourceType::Water, StartingWater);
	//ResourceManagerComp->AddResource(EResourceType::Food, StartingFood);

}



