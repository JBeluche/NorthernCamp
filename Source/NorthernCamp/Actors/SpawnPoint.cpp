// Copyright Creating Mountains!


#include "NorthernCamp/Actors/SpawnPoint.h"

#include "EngineUtils.h"
#include "NavigationSystem.h"
#include "Components/SphereComponent.h"
#include "NorthernCamp/Characters/CharacterSettler.h"
#include "NorthernCamp/Characters/Components/CharacterCustomizationComponent.h"
#include "NorthernCamp/Controllers/GenerateSettlerController.h"
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
	
	const ConstructorHelpers::FClassFinder<AActor> ItemBlueprint(TEXT("/Game/Blueprints/Pawns/BP_RaidingBoatActor"));

	BoatBlueprintClass = ItemBlueprint.Class;

}


void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();
}

void ASpawnPoint::SpawnRaiders(TArray<TSubclassOf<AActor>> RaidersClassToSpawn)
{
	FActorSpawnParameters SpawnParams;
	SpawnedRaiders.Empty();

	for (int32 i = 0; i < RaidersClassToSpawn.Num(); i++)
	{
		ACharacterBase* SpawnedCharacter = GetWorld()->SpawnActor<ACharacterBase>(RaidersClassToSpawn[i], GetActorLocation(), GetActorRotation(), SpawnParams);
		if (SpawnedCharacter){
			FCharacterSetupSettings CharacterSetupSettings;
			CharacterSetupSettings.CharacterStance = ECurrentStance::Attacking;
			SpawnedCharacter->SetupCharacter(CharacterSetupSettings);
			//This should be deleted
			SpawnedRaiders.Add(SpawnedCharacter);
		}
	}
	/*
	if(bIsBoatSpawn)
	{
		ARaidingBoatActor* SpawnedBoat = SpawnBoat();
		if(SpawnedBoat)
		{
			if (GetWorld()){

				//Foreach in the tmap
				for (int32 i = 0; i < RaidersClassToSpawn.Num(); i++)
				{
					//if(!Cast<ACharacterBase>(RaidersClassToSpawn[i])){UE_LOG(LogTemp, Error, TEXT("ASpawnPoint::SpawnRaiders could not cast RaidersClassToSpawn")); return;}
					ACharacterBase* SpawnedCharacter = GetWorld()->SpawnActor<ACharacterBase>(RaidersClassToSpawn[i], GetActorLocation(), GetActorRotation(), SpawnParams);
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
	}*/

}

ACharacterBase* ASpawnPoint::SpawnCharacter(TSubclassOf<AActor> CharactersToSpawn)
{
	UE_LOG(LogTemp, Warning, TEXT("SpawnCharacter!"));

	FActorSpawnParameters SpawnParams;
	
	UNavigationSystemV1* NavigationSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	if(NavigationSystem == nullptr){UE_LOG(LogTemp, Warning, TEXT("ASpawnPoint::SpawnCharacter nullptr NavigationSystem")); return nullptr;}
	FNavLocation ResultLocation;
	
	NavigationSystem->GetRandomPointInNavigableRadius(GetActorLocation(), BoatDockingSphere->GetScaledSphereRadius(), ResultLocation);
	ResultLocation.Location.Z = ResultLocation.Location.Z + 200.0f; 
	if (GetWorld())
	{
		ACharacterBase* SpawnedCharacter = GetWorld()->SpawnActor<ACharacterBase>(CharactersToSpawn, ResultLocation.Location, GetActorRotation(), SpawnParams);
	
		
		return SpawnedCharacter;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("nthere is no world!"));

	}

	return nullptr;

}

ARaidingBoatActor* ASpawnPoint::SpawnBoat()
{
	if (GetWorld()){
		FActorSpawnParameters SpawnParams;
		ARaidingBoatActor* SpawnedBoat = GetWorld()->SpawnActor<ARaidingBoatActor>(BoatBlueprintClass, GetActorLocation(), GetActorRotation(), SpawnParams);
		if (SpawnedBoat){
			return SpawnedBoat;
		}
	}

	return nullptr;
}

bool ASpawnPoint::CanSpawn(UClass* ClassToCheck)
{
	for(UClass* Class : SpawnableClasses)
	{
		if(ClassToCheck == Class)
		{
			return true;
		}
	}
	return false;


}

