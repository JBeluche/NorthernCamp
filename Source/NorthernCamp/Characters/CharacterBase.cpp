// Fill out your copyright notice in the Description page of Project Settings.


#include "NorthernCamp/Characters/CharacterBase.h"

#include "Components/CharacterCustomizationComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	//This was needed to generated a SKMESH using modular character
	Mask = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mask"));
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));

	Mask->SetupAttachment(RootComponent);
	SkeletalMesh->SetupAttachment(Mask);

	//Because the charater mesh always looks the wrong way and is to high
	FRotator NewRotation = SkeletalMesh->GetComponentRotation();
	NewRotation.Yaw = SkeletalMesh->GetComponentRotation().Yaw - 90.0f;
	FVector NewPosition = SkeletalMesh->GetComponentLocation();
	NewPosition.Z = SkeletalMesh->GetComponentLocation().Z - 90.0f;
	
	SkeletalMesh->SetRelativeRotation(NewRotation);
	SkeletalMesh->SetRelativeLocation(NewPosition);

	CharacterCustomizationComponent = CreateDefaultSubobject<UCharacterCustomizationComponent>(TEXT("Character Customization Component"));


}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->bUseRVOAvoidance = true;



}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool ACharacterBase::WithinActionRadius(AActor* Actor)
{
	const float TempDistance = FVector::Dist(GetActorLocation(), Actor->GetActorLocation());

	UE_LOG(LogTemp, Error, TEXT("The distance from the player is: %f and the radius is: %f"), TempDistance, ActionRadius);
	if(TempDistance < ActionRadius)
	{
		return true;	
	}

	return false;
}

void ACharacterBase::SetSkeletalMesh(USkeletalMesh *GeneratedSkeletalMesh)
{
	SkeletalMesh->SetSkeletalMesh(GeneratedSkeletalMesh, true);
}
