// Copyright Creating Mountains!


#include "NorthernCamp/Actors/ResourceBaseActor.h"

// Sets default values
AResourceBaseActor::AResourceBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

}

// Called when the game starts or when spawned
void AResourceBaseActor::BeginPlay()
{
	Super::BeginPlay();
	
}

