// Copyright Creating Mountains!


#include "NorthernCamp/Actors/SpawnPoint.h"

#include "Components/SphereComponent.h"
#include "NorthernCamp/Controllers/RaidController.h"

// Sets default values
ASpawnPoint::ASpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);
	
	BoatDockingSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Spawn radius"));
	BoatDockingSphere->SetupAttachment(SceneComponent);

	//static ConstructorHelpers::FObjectFinder<UBlueprint> ItemBlueprint(TEXT("Blueprint'/Game/Blueprints/Pawns/BP_RaidingBoatActor.BP_RaidingBoatActor'"));

	/*
	if (ItemBlueprint.Object){
		BoatBlueprint = (UClass*)ItemBlueprint.Object->GeneratedClass;
	}

	*/

	
	const ConstructorHelpers::FClassFinder<AActor> ItemBlueprint(TEXT("/Game/Blueprints/Pawns/BP_RaidingBoatActor"));

	BoatBlueprintClass = ItemBlueprint.Class;

	
	/*const ConstructorHelpers::FClassFinder<AActor> BP_Raider01(TEXT("Blueprint'/Game/Blueprints/Characters/SeaRaiders/SeaRainder_01.SeaRainder_01'"));

	RaiderBlueprintClass = BP_Raider01.Class;*/



}

// Called when the game starts or when spawned
void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	World = GetWorld();
}

void ASpawnPoint::SpawnRaiders(TArray<TSubclassOf<AActor>> RaidersClassToSpawn)
{
	if(bIsBoatSpawn)
	{
		ARaidingBoatActor* SpawnedBoat = SpawnBoat();
		if(SpawnedBoat)
		{
			if (World){
				FActorSpawnParameters SpawnParams;

				//Foreach in the tmap
				for (int32 i = 0; i < RaidersClassToSpawn.Num(); i++)
				{
					//if(!Cast<ACharacterBase>(RaidersClassToSpawn[i])){UE_LOG(LogTemp, Error, TEXT("ASpawnPoint::SpawnRaiders could not cast RaidersClassToSpawn")); return;}
					ACharacterBase* SpawnedCharacter = World->SpawnActor<ACharacterBase>(RaidersClassToSpawn[i], GetActorLocation(), GetActorRotation(), SpawnParams);
					if (SpawnedCharacter){
						FCharacterSetupSettings CharacterSetupSettings;
						CharacterSetupSettings.CharacterStance = ECurrentStance::Attacking;
						CharacterSetupSettings.bShouldBeFrozen = true;
						SpawnedCharacter->SetupCharacter(CharacterSetupSettings);
						SpawnedRaiders.Add(SpawnedCharacter);
					}
				}
				SpawnedBoat->AttachRaiders(SpawnedRaiders);
				SpawnedBoat->TargetLocation = BoatDockingSphere->GetComponentLocation();
				SpawnedBoat->StartMoving = true;

			}
		}
	}
}

ARaidingBoatActor* ASpawnPoint::SpawnBoat()
{
	World = GetWorld();

	if (World){
		FActorSpawnParameters SpawnParams;
		ARaidingBoatActor* SpawnedBoat = World->SpawnActor<ARaidingBoatActor>(BoatBlueprintClass, GetActorLocation(), GetActorRotation(), SpawnParams);
		if (SpawnedBoat){
			return SpawnedBoat;
		}
	}

	return nullptr;
}

