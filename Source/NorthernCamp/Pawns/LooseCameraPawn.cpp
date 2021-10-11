// Fill out your copyright notice in the Description page of Project Settings.


#include "NorthernCamp/Pawns/LooseCameraPawn.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "Landscape.h"
#include "GameFramework/SpringArmComponent.h"

ALooseCameraPawn::ALooseCameraPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	RootComponent = BoxComponent;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->SetupAttachment(RootComponent);
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

}

// Called when the game starts or when spawned
void ALooseCameraPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALooseCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetPositionRelativeToLandscape();
}

// Called to bind functionality to input
void ALooseCameraPawn::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


//FIXME Execute this function only when the finger is swipping and or in a timer. Not when ticking.
void ALooseCameraPawn::SetPositionRelativeToLandscape()
{
	TArray<FHitResult> OutHits;
	
	FVector StartLocation = GetActorLocation();
	FVector EndLocation = FVector(StartLocation.X, StartLocation.Y, (StartLocation.Z - 10000.0f));

	FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
	RV_TraceParams.bTraceComplex = true;
	RV_TraceParams.bReturnPhysicalMaterial = false;
	
	FHitResult RV_Hit(ForceInit);
		
	GetWorld()->LineTraceSingleByChannel(
		RV_Hit,        		//result
		StartLocation,   	//start
		EndLocation, 		//end
		ECC_Pawn, 			//collision channel
		RV_TraceParams
	);

	if(RV_Hit.bBlockingHit)
	{
		if(Cast<ALandscape>(RV_Hit.Actor))
		{
			SetActorLocation(FVector(StartLocation.X, StartLocation.Y, (RV_Hit.ImpactPoint.Z + CameraHeight)));
		}
	}
}

//Check if the camera is still inside the bounds of the hero he should follow
FVector ALooseCameraPawn::GetSelectedHeroPosition()
{
	UE_LOG(LogTemp, Error, TEXT("Giving you the vector"));

	return FVector(0.0f, 0.0f, 0.0f);
}

