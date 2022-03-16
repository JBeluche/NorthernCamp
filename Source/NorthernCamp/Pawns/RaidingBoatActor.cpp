// Copyright Creating Mountains!


#include "NorthernCamp/Pawns/RaidingBoatActor.h"

#include "NavigationSystem.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NorthernCamp/Actors/Components/BoatSeat.h"
#include "NorthernCamp/Characters/CharacterBase.h"
#include "TimerManager.h"

// Sets default values
ARaidingBoatActor::ARaidingBoatActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base mesh"));
	MeshComp->SetupAttachment(SceneComponent);

	


}

// Called when the game starts or when spawned
void ARaidingBoatActor::BeginPlay()
{
	Super::BeginPlay();

	//Get amount of boat seats
	TInlineComponentArray<UBoatSeat*> BoatSeats;
	GetComponents(BoatSeats);
	
	NumberOfSeats = BoatSeats.Num();


}

void ARaidingBoatActor::Tick(float DeltaTime)
{


	if(StartMoving && bSetupCompleted == false)
	{
		SetupMoveCoordinations();
	}
	
	if (CurrentDistance < TotalDistance && StartMoving && bSetupCompleted) 
	{
		FVector Location = GetActorLocation();
		FVector NewLocation = Location + (Direction * BoatSpeed * DeltaTime);
		SetActorLocation(NewLocation);
		CurrentDistance = (Location - StartLocation).Size();
	}
	else if(!bEveryonesOut)
	{
		GetWorld()->GetTimerManager().SetTimer(DisembarkTimerHandle, this, &ARaidingBoatActor::Disembark, TimeBeforeDisembarking, false);
		bEveryonesOut = true;
	}
}

void ARaidingBoatActor::SetupMoveCoordinations()
{

	StartLocation = GetActorLocation();

	//Moving the boat
	TargetLocation.Z = StartLocation.Z;

	Direction = TargetLocation - StartLocation;

	TotalDistance = Direction.Size();

	// Get Normal Direction
	Direction = Direction.GetSafeNormal();
	CurrentDistance = 0.0f;

	bSetupCompleted = true;

	
}

void ARaidingBoatActor::AttachRaiders(TArray<ACharacterBase*> RaidersToAttach)
{
	int32 i = 0;
	//Set all raiders to frozen
	RaidersOnBoat = RaidersToAttach;
	//Get all spots and attach raiders to it.
	TInlineComponentArray<UBoatSeat*> BoatSeats;

	GetComponents(BoatSeats);

	for (auto CompIt = BoatSeats.CreateConstIterator(); CompIt; ++CompIt)
	{
		if(RaidersToAttach.Num() <= i)
		{
			return;
		}
		RaidersToAttach[i]->GetCharacterMovement()->SetDefaultMovementMode();
		RaidersToAttach[i]->SetActorLocation(Cast<UBoatSeat>(*CompIt)->GetComponentLocation());
		i++;
	}

	
}

void ARaidingBoatActor::Disembark()
{
	UNavigationSystemV1* NavigationSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	FNavLocation ResultLocation;

	UE_LOG(LogTemp, Error, TEXT("Tick tack"));

	if(NavigationSystem == nullptr){UE_LOG(LogTemp, Warning, TEXT("ARaidingBoatActor::Disembark nullptr NavigationSystem")); return;}

	//For each raider, get a free spot on the navmesh and move him there.
	
	for(ACharacterBase* Raider : RaidersOnBoat)
	{
		NavigationSystem->GetRandomPointInNavigableRadius(GetActorLocation(), MaxRadiusDisambarkSpawn, ResultLocation);
		FVector NewLocation = ResultLocation.Location;
		NewLocation.Z += BoatHeightFalling;
		Raider->SetActorLocation(NewLocation);
				
	}
}




