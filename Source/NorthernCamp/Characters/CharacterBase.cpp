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
	SkeletalMesh->SetupAttachment(RootComponent);

	//Because the charater mesh always looks the wrong way and is to high
	FRotator NewRotation = SkeletalMesh->GetComponentRotation();
	NewRotation.Yaw = SkeletalMesh->GetComponentRotation().Yaw - 90.0f;
	FVector NewPosition = SkeletalMesh->GetComponentLocation();
	NewPosition.Z = SkeletalMesh->GetComponentLocation().Z - 90.0f;
	
	SkeletalMesh->SetRelativeRotation(NewRotation);
	SkeletalMesh->SetRelativeLocation(NewPosition);
	
	GetMesh()->SetRelativeRotation(NewRotation);
	GetMesh()->SetRelativeLocation(NewPosition);

	CharacterCustomizationComponent = CreateDefaultSubobject<UCharacterCustomizationComponent>(TEXT("Character Customization Component"));

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	bUseControllerRotationYaw = false;

	AIControllerClass = AAIControllerBase::StaticClass();

	//Animation
	static ConstructorHelpers::FObjectFinder<UAnimMontage> BP_AttackAnimation(TEXT("AnimMontage'/Game/_Character/Modular/Animations/Montage_AttackUnarmed.Montage_AttackUnarmed'"));
	AttackAnimation = BP_AttackAnimation.Object;

	const ConstructorHelpers::FClassFinder<UAnimInstance> BP_AnimaBp(TEXT("/Game/_Character/Modular/Animations/ABP_Poly"));
	AnimBlueprintClass = BP_AnimaBp.Class;

}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	SpawnDefaultController();

	AIController = Cast<AAIControllerBase>(GetController());
	if(AIController == nullptr){UE_LOG(LogTemp, Error, TEXT("ACharacterBase::BeginPlay nullptr for AIController")); return;}

	AIController->SetupController();
	bDiedOrWounded = false;

}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(GetCharacterMovement()->Velocity.Size() > 0.0f)
	{
		SetCanAffectNavigationGeneration(false, true) ;
	}
	else
	{
		SetCanAffectNavigationGeneration(true, true) ;
	}
}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

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
	if(SkeletalMesh->GetAnimInstance() == nullptr)	{UE_LOG(LogTemp, Warning, TEXT("ACharacterBase::PauseAnimation nulpptr GetAnimInstance")); return;	}

	SkeletalMesh->GetAnimInstance()->Montage_Play(MontageToPlay, 1, EMontagePlayReturnType::MontageLength, 0.0f);
}
void ACharacterBase::PauseAnimation(UAnimMontage* MontageToPause)
{
	if(SkeletalMesh->GetAnimInstance() == nullptr)	{UE_LOG(LogTemp, Warning, TEXT("ACharacterBase::PauseAnimation nulpptr GetAnimInstance")); return;	}
	SkeletalMesh->GetAnimInstance()->Montage_Pause(MontageToPause);

}

void ACharacterBase::ResumeAnimation(UAnimMontage* MontageToResume)
{
	if(SkeletalMesh->GetAnimInstance() == nullptr)	{UE_LOG(LogTemp, Warning, TEXT("ACharacterBase::PauseAnimation nulpptr GetAnimInstance")); return;	}
	SkeletalMesh->GetAnimInstance()->Montage_Resume(MontageToResume);
}

TSubclassOf<UAnimInstance> ACharacterBase::GetAnimBpClass()
{
	return AnimBlueprintClass;
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

void ACharacterBase::Died()
{
	SetFrozen(true);
	bDiedOrWounded = true;
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &ACharacterBase::DestroyActor, 30.0f, false);

}

void ACharacterBase::DestroyActor()
{
	UE_LOG(LogTemp, Warning, TEXT("Should be destroyed!!!!"));
	Destroy();
}

void ACharacterBase::Healed()
{
	bDiedOrWounded = false;
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
	if(AIController == nullptr){UE_LOG(LogTemp, Warning, TEXT("ACharacterBase::SetupCharacter nullptr for AIController"));}
	AIController->SetBehaviorTree(ECurrentStance::Attacking);
	
	//Change faction?
	
}

void ACharacterBase::SetFrozen(bool bIsFrozen)
{
	AIController->SetCharacterIsFrozen(bIsFrozen);
}