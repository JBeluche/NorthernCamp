// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

class UCharacterCustomizationComponent;

UENUM()
enum class ECurrentStance : uint8 
{
	Settler UMETA(DisplayName = "Settler"),
	Defending UMETA(DisplayName = "Defending"),
	Attacking UMETA(DisplayName = "Attacking"),
};

UENUM()
enum class EFactions : uint8 
{
	None UMETA(DisplayName = "None"),
	Novard UMETA(DisplayName = "Novard"),
	Raider UMETA(DisplayName = "Raider"),
};



UCLASS()
class NORTHERNCAMP_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	float CurrentSleep = 100.0f;
	float CurrentHunger = 100.0f;
	float CurrentThirst = 100.0f;
	float CurrentHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float ActionRadius = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	EFactions Faction;

	bool WithinActionRadius(AActor* Actor);
	void SetSkeletalMesh(USkeletalMesh* GeneratedSkeletalMesh);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Building)
	USkeletalMesh* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mask;
		
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	UCharacterCustomizationComponent* CharacterCustomizationComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	ECurrentStance CurrentStance;

};
