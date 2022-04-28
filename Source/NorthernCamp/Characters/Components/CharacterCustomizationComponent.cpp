// Copyright CreatingMountains


#include "NorthernCamp/Characters/Components/CharacterCustomizationComponent.h"

#include "NorthernCamp/BlueprintFunctions/MeshMergeFunctionLibrary.h"
#include "NorthernCamp/Characters/CharacterBase.h"

// Sets default values for this component's properties
UCharacterCustomizationComponent::UCharacterCustomizationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;


	//Material insteance
	const ConstructorHelpers::FObjectFinder<UMaterialInterface> BP_MainMaterial(TEXT("Material'/Game/_Character/ModularCharacters/Materials/ModularFantasyHeroCharacters.ModularFantasyHeroCharacters'"));
	const ConstructorHelpers::FObjectFinder<UMaterialInterface> BP_MaskMaterial(TEXT("Material'/Game/_Character/ModularCharacters/Materials/Mask.Mask'"));
	
	const ConstructorHelpers::FObjectFinder<USkeleton> BP_SK_Skeleton(TEXT("/Game/_Character/Modular/Meshes/SK_Polygon"));


	const ConstructorHelpers::FObjectFinder<USkeletalMesh> BP_SKMBaseSettlerFemale(TEXT("/Game/_Character/Modular/Meshes/SettlerFemalBase"));
	const ConstructorHelpers::FObjectFinder<USkeletalMesh> BP_SKMBaseSettlerMale(TEXT("/Game/_Character/Modular/Meshes/SettlerMaleBase"));


	//Mesh reference
	if(BP_MainMaterial.Succeeded())	{MainMaterial = BP_MainMaterial.Object;}
	if(BP_MaskMaterial.Succeeded())	{MaskMaterial = BP_MaskMaterial.Object;}
	if(BP_SK_Skeleton.Succeeded()){	SkeletonToUse = BP_SK_Skeleton.Object;}
	if(BP_SKMBaseSettlerFemale.Succeeded()){SkeletalMeshBaseFemale = BP_SKMBaseSettlerFemale.Object;}
	if(BP_SKMBaseSettlerMale.Succeeded()){SkeletalMeshBaseMale = BP_SKMBaseSettlerMale.Object;}


}


// Called when the game starts
void UCharacterCustomizationComponent::BeginPlay()
{
	Super::BeginPlay();

	Character = Cast<ACharacterBase>(GetOwner());

	if(Character && !bHasCustomAnimation)
	{
		Character->SkeletalMesh->SetSkeletalMesh(nullptr);
		Character->GetMesh()->SetSkeletalMesh(nullptr);
		
		SetArmorLevel(CurrentArmorLevel);
		
		GenerateAllMaterials();
		GenerateMeshes();
		
		Character->SkeletalMesh->SetAnimInstanceClass(Character->GetAnimBpClass());
		Character->SkeletalMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	}
}

void UCharacterCustomizationComponent::GenerateMeshes()
{
	if(Hair == nullptr)
	{
		Character->SkeletalMesh->SetSkeletalMesh(nullptr);
		Character->GetMesh()->SetSkeletalMesh(nullptr);
		Character->Mask->SetSkeletalMesh(nullptr);
	}
	else
	{
		FSkeletalMeshMergeParams MergeParams;
		MergeParams.MeshesToMerge = GetAllMeshesToMerge();

		MergeParams.Skeleton = SkeletonToUse;
		USkeletalMesh* GeneratedSkeletalMesh = UMeshMergeFunctionLibrary::MergeMeshes(MergeParams); 

		if(IsValid(GeneratedSkeletalMesh))
		{
			Character->SetSkeletalMesh(GeneratedSkeletalMesh);

		}
	}
	Character->SkeletalMesh->SetSkeletalMesh(nullptr);
	Character->GetMesh()->SetSkeletalMesh(nullptr);
	Character->Mask->SetSkeletalMesh(nullptr);

	//Generate custom mesh

}

TArray<USkeletalMesh*> UCharacterCustomizationComponent::GetAllMeshesToMerge()
{

	if(Head) {MeshesToMerge.Add(Head);}
	if(Eyebrows) {MeshesToMerge.Add(Eyebrows);}
	if(Hair) {MeshesToMerge.Add(Hair);}

	if(FacialHair) {MeshesToMerge.Add(FacialHair);}

	if(StaticBody){MeshesToMerge.Add(StaticBody);}
	
	if(ExtraHair) {MeshesToMerge.Add(ExtraHair);}
	
	//I think does are ears 
	if(Extras) {MeshesToMerge.Add(Extras);}

	if(Torso) {MeshesToMerge.Add(Torso);}
	if(ArmUpperRight) {MeshesToMerge.Add(ArmUpperRight);}

	if(ArmUpperLeft) {MeshesToMerge.Add(ArmUpperLeft);}
	if(ArmLowerRight) {MeshesToMerge.Add(ArmLowerRight);}
	if(ArmLowerLeft) {MeshesToMerge.Add(ArmLowerLeft);}
	if(HandRight) {MeshesToMerge.Add(HandRight);}
	if(HandLeft) {MeshesToMerge.Add(HandLeft);}

	if(Hips) {MeshesToMerge.Add(Hips);}
	if(LegRight) {MeshesToMerge.Add(LegRight);}
	if(LegLeft) {MeshesToMerge.Add(LegLeft);}

		
	//Armor Extras
	if(ShoulderAttachmentRight) {MeshesToMerge.Add(ShoulderAttachmentRight);}
	if(ShoulderAttachmentLeft) {MeshesToMerge.Add(ShoulderAttachmentLeft);}
	if(ElbowAttachmentRight) {MeshesToMerge.Add(ElbowAttachmentRight);}
	if(ElbowAttachmentLeft) {MeshesToMerge.Add(ElbowAttachmentLeft);}
	if(KneeAttachmentRight) {MeshesToMerge.Add(KneeAttachmentRight);}
	if(KneeAttachmentLeft) {MeshesToMerge.Add(KneeAttachmentLeft);}



	//Overall Attachments
	if(BackAttachment) {MeshesToMerge.Add(BackAttachment);}
	if(HipAttachment) {MeshesToMerge.Add(HipAttachment);}

	if(ChestAttachment) {MeshesToMerge.Add(ChestAttachment);} //Seems to not exist(no sk for it?)

	//Headwear
	if(HeadAttachmentHair) {MeshesToMerge.Add(HeadAttachmentHair);}
	if(HeadAttachmentHelmet) {MeshesToMerge.Add(HeadAttachmentHelmet);}
	
	if(HeadCoveringsBaseHair) {MeshesToMerge.Add(HeadCoveringsBaseHair);}
	if(HeadCoveringsNoFacialHair) {MeshesToMerge.Add(HeadCoveringsNoFacialHair);}
	if(HeadCoveringsNoHair) {MeshesToMerge.Add(HeadCoveringsNoHair);}


	return MeshesToMerge;
}


// SETUP MATERIALS 

void UCharacterCustomizationComponent::GenerateAllMaterials()
{

	if(!MainMaterial){UE_LOG(LogTemp, Warning, TEXT("%s's CharacterCustomizationComponent: Material is nullptr in GenreateAllMaterials"), *Character->GetName()); return;}

	if(!Character->SkeletalMesh){return;}
	DynamicMaterial = Character->SkeletalMesh->CreateDynamicMaterialInstance(0, MainMaterial);

	Character->Mask->SetMaterial(0, MaskMaterial);

	//Set all the colors here!
	DynamicMaterial->SetVectorParameterValue( FName("Color_Skin"), LinearColorSkin);
	DynamicMaterial->SetVectorParameterValue( FName("Color_Primary"), LinearColorPrimary);
	DynamicMaterial->SetVectorParameterValue( FName("Color_Secondary"), LinearColorSecondary);
	DynamicMaterial->SetVectorParameterValue( FName("Color_Metal_Primary"), LinearColorMetalPrimary);
	DynamicMaterial->SetVectorParameterValue( FName("Color_Metal_Secondary"), LinearColorMetalSecondary);
	
	DynamicMaterial->SetVectorParameterValue( FName("Color_Stubble"), LinearColorStubble);
	DynamicMaterial->SetVectorParameterValue( FName("Color_Scar"), LinearColorScar);
	DynamicMaterial->SetVectorParameterValue( FName("Color_Metal_Dark"), LinearColorMetalDark);
	DynamicMaterial->SetVectorParameterValue( FName("Color_Leather_Primary"), LinearColorLeatherPrimary);
	DynamicMaterial->SetVectorParameterValue( FName("Color_Leather_Secondary"), LinearColorLeatherSecondary);
	DynamicMaterial->SetVectorParameterValue( FName("Color_Hair"), LinearColorHair);
	DynamicMaterial->SetVectorParameterValue( FName("Color_BodyArt"), LinearColorBodyArt);

}

void UCharacterCustomizationComponent::SetArmorLevel(EArmorLevel NewArmorLevel)
{
	CurrentArmorLevel = NewArmorLevel;


	
		
	
	if(NewArmorLevel == EArmorLevel::Level_0)
	{
		if(CharacterBodyType == EBodyType::PeasantLevel0)
		{
			
			Torso = nullptr;
			ArmUpperRight = nullptr;
			ArmUpperLeft = nullptr;
			ArmLowerRight = nullptr;
			ArmLowerLeft = nullptr;
			HandRight = nullptr;
			HandLeft = nullptr;
			Hips = nullptr;
			LegRight = nullptr;
			LegLeft = nullptr;

			if(bIsFemale)
			{
				StaticBody = SkeletalMeshBaseFemale;
			}
			else
			{
				StaticBody = SkeletalMeshBaseMale;
			}


		}
	}
	else if(NewArmorLevel == EArmorLevel::Level_1)
	{
		//Set all the meshes to the ones you want for level 1 armor.
		
	}
	else if(NewArmorLevel == EArmorLevel::Level_2)
	{
		
	}
	else if(NewArmorLevel == EArmorLevel::Level_3)
	{
		
	}
	else if(NewArmorLevel == EArmorLevel::Level_4)
	{
		
	}
	else if(NewArmorLevel == EArmorLevel::Level_5)
	{
		
	}
	else if(NewArmorLevel == EArmorLevel::Level_6)
	{
		
	}
}
