// Copyright Creating Mountains!


#include "NorthernCamp/Pawns/CampCameraPawn.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ACampCameraPawn::ACampCameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	RootComponent = SpringArmComponent;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ACampCameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called to bind functionality to input
void ACampCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

