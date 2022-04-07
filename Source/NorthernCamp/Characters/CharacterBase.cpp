// Fill out your copyright notice in the Description page of Project Settings.


#include "NorthernCamp/Characters/CharacterBase.h"

#include "NorthernCamp/AIController/AIControllerBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/CharacterCustomizationComponent.h"
#include "Components/VitalsComponentBase.h"
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
	VitalsComponent = CreateDefaultSubobject<UVitalsComponentBase>(TEXT("Vitals Component"));

	Mask->SetupAttachment(RootComponent);
	SkeletalMesh->SetupAttachment(Mask);

	//Because the charater mesh always looks the wrong way and is to high
	FRotator NewRotation = SkeletalMesh->GetComponentRotation();
	NewRotation.Yaw = SkeletalMesh->GetComponentRotation().Yaw - 90.0f;
	FVector NewPosition = SkeletalMesh->GetComponentLocation();
	NewPosition.Z = SkeletalMesh->GetComponentLocation().Z - 90.0f;
	
	SkeletalMesh->SetRelativeRotation(NewRotation);
	SkeletalMesh->SetRelativeLocation(NewPosition);

	//Setting a cube, so clicking on actors is easier.
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ReferenceObject(TEXT("/Game/_Character/Modular/Meshes/SKM_Polygon_Base"));
	BaseMesh = ReferenceObject.Object;
	GetMesh()->SetSkeletalMesh(BaseMesh);

	
	GetMesh()->SetRelativeRotation(NewRotation);
	GetMesh()->SetRelativeLocation(NewPosition);

	CharacterCustomizationComponent = CreateDefaultSubobject<UCharacterCustomizationComponent>(TEXT("Character Customization Component"));

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;


	AIControllerClass = AAIControllerBase::StaticClass();

	static ConstructorHelpers::FObjectFinder<UAnimMontage> BP_AttackAnimation(TEXT("AnimMontage'/Game/_Character/Modular/Animations/PolygonAttackUnarmed_1_Montage.PolygonAttackUnarmed_1_Montage'"));
	AttackAnimation = BP_AttackAnimation.Object;
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	
	//GetCharacterMovement()->bUseRVOAvoidance = true;

	GetMesh()->SetSkeletalMesh(nullptr);


	SpawnDefaultController();

	AIController = Cast<AAIControllerBase>(GetController());

	if(AIController == nullptr){UE_LOG(LogTemp, Error, TEXT("ACharacterBase::BeginPlay nullptr for AIController")); return;}

	AIController->SetupController();


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

// Todo
// Make get componment and get animations with enums for componenets and animations

UVitalsComponentBase* ACharacterBase::GetVitals()
{
	return VitalsComponent;
}

UAnimMontage* ACharacterBase::GetAttackAnimation()
{
	return AttackAnimation;
}

void ACharacterBase::PlayAnimationMontage(UAnimMontage* MontageToPlay, bool bIsLooping)
{
	SkeletalMesh->GetAnimInstance()->Montage_Play(MontageToPlay, 1, EMontagePlayReturnType::MontageLength, 0.0f);
}
void ACharacterBase::PauseAnimation(UAnimMontage* MontageToPause)
{
	SkeletalMesh->GetAnimInstance()->Montage_Pause(MontageToPause);
}

void ACharacterBase::ResumeAnimation(UAnimMontage* MontageToResume)
{
	SkeletalMesh->GetAnimInstance()->Montage_Resume(MontageToResume);
}
float ACharacterBase::GetAttackRange()
{
	return AttackRange;
}

float ACharacterBase::GetWeaponDamage()
{
	return WeaponDamage;
}

bool ACharacterBase::WithinActionRadius(AActor* Actor)
{
	const float TempDistance = FVector::Dist(GetActorLocation(), Actor->GetActorLocation());

	
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

void ACharacterBase::SetupCharacter(FCharacterSetupSettings CharacterSettings)
{
	//Set to frozen?
	AIController->SetCharacterIsFrozen(CharacterSettings.bShouldBeFrozen);
	CurrentStance = CharacterSettings.CharacterStance;
	//Set behavior tree?
	if(AIController == nullptr){UE_LOG(LogTemp, Warning, TEXT("ACharacterBase::SetupCharacter nullptr for AIController"))}
	AIController->SetBehaviorTree(ECurrentStance::Attacking);
	
	//Change faction?
	
}

void ACharacterBase::SetFrozen(bool bIsFrozen)
{
	AIController->SetCharacterIsFrozen(bIsFrozen);
}