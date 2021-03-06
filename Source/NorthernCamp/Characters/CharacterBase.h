// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

class UCharacterCustomizationComponent;
class AAIControllerBase;
class UVitalsComponentBase;

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
	SeaClan UMETA(DisplayName = "Sea Clan"),
	Wolf UMETA(DisplayName = "Wolf"),
	Bandit UMETA(DisplayName = "Bandit"),
};

//Structs

USTRUCT(BlueprintType)
struct FCharacterSetupSettings
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Setup Settings")
	EFactions Faction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Setup Settings")
	ECurrentStance CharacterStance;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Setup Settings")
	bool bShouldBeFrozen;

};

//Class
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

	//Variables
	AAIControllerBase* AIController;
	UVitalsComponentBase* VitalsComponent;
	FTimerHandle DestroyTimerHandle;
	TSubclassOf<UAnimInstance> AnimBlueprintClass;

	//UPROPERTY
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Squad Settings")
	float AttackRange = 100.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Squad Settings")
	float WeaponDamage = 20.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Squad Settings")
	UAnimMontage* AttackAnimation;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Functions
	UVitalsComponentBase* GetVitals();
	UAnimMontage * GetAttackAnimation();
	float GetAttackRange();
	float GetWeaponDamage();
	
	void PlayAnimationMontage(UAnimMontage* MontageToPlay, bool bIsLooping);
	void PauseAnimation(UAnimMontage* MontageToPause);
	void ResumeAnimation(UAnimMontage* MontageToResume);
	TSubclassOf<UAnimInstance>  GetAnimBpClass();
	
	//UFUNCTION()
	UFUNCTION()
	void DestroyActor();
	
	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Squad Settings")
	bool bIsSquadLeader;
	
	ACharacterBase* CurrentSquadLeader;
	bool bIsHero = false;


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
	void SetupCharacter(FCharacterSetupSettings CharacterSettings);
	void SetFrozen(bool bIsFrozen);
	void Died();
	void Healed();


	//UPROPERTY
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mask;
		
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	UCharacterCustomizationComponent* CharacterCustomizationComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	ECurrentStance CurrentStance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	bool bDiedOrWounded;

};
