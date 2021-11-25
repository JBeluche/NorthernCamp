// Fill out your copyright notice in the Description page of Project Settings.


#include "NorthernCamp/Characters/CharacterBase.h"

#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
