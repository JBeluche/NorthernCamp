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

	


}


// Called when the game starts
void UCharacterCustomizationComponent::BeginPlay()
{
	Super::BeginPlay();

	//Generate the meshes using the meshmerge function
	
	FSkeletalMeshMergeParams MergeParams;
	MergeParams.MeshesToMerge = GetAllMeshesToMerge();

	MergeParams.Skeleton = Skeleton;
	USkeletalMesh* GeneratedSkeletalMesh = UMeshMergeFunctionLibrary::MergeMeshes(MergeParams); 

	ACharacterBase* Character = Cast<ACharacterBase>(GetOwner());
	if(Character)
	{
		if(IsValid(GeneratedSkeletalMesh))
		{
			Character->SetSkeletalMesh(GeneratedSkeletalMesh);
		}
	}
}

TArray<USkeletalMesh*> UCharacterCustomizationComponent::GetAllMeshesToMerge()
{

	if(Head) {MeshesToMerge.Add(Head);}
	if(Eyebrows) {MeshesToMerge.Add(Eyebrows);}
	if(FacialHair) {MeshesToMerge.Add(FacialHair);}
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
	if(Hair) {MeshesToMerge.Add(Hair);}

	//Attachments
	if(HeadAttachmentHair) {MeshesToMerge.Add(HeadAttachmentHair);}
	if(HeadAttachmentHelmet) {MeshesToMerge.Add(HeadAttachmentHelmet);}
	if(ChestAttachment) {MeshesToMerge.Add(ChestAttachment);}
	if(HeadCoveringsBaseHair) {MeshesToMerge.Add(HeadCoveringsBaseHair);}
	if(HeadCoveringsNoFacialHair) {MeshesToMerge.Add(HeadCoveringsNoFacialHair);}
	if(HeadCoveringsNoHair) {MeshesToMerge.Add(HeadCoveringsNoHair);}

	if(BackAttachment) {MeshesToMerge.Add(BackAttachment);}
	if(ShoulderAttachmentRight) {MeshesToMerge.Add(ShoulderAttachmentRight);}
	if(ShoulderAttachmentLeft) {MeshesToMerge.Add(ShoulderAttachmentLeft);}
	if(ElbowAttachmentRight) {MeshesToMerge.Add(ElbowAttachmentRight);}
	if(ElbowAttachmentLeft) {MeshesToMerge.Add(ElbowAttachmentLeft);}

	if(HipAttachment) {MeshesToMerge.Add(HipAttachment);}

	if(KneeAttachmentRight) {MeshesToMerge.Add(KneeAttachmentRight);}
	if(KneeAttachmentLeft) {MeshesToMerge.Add(KneeAttachmentLeft);}
	if(Extras) {MeshesToMerge.Add(Extras);}

	return MeshesToMerge;
}

/* SETUP MATERIALS */

void UCharacterCustomizationComponent::SetColorSkin(uint8 Value)
{
	ColorSkin = Value;
}

void UCharacterCustomizationComponent::SetColorPrimary(uint8 Value)
{
	ColorPrimary = Value;
}

void UCharacterCustomizationComponent::SetColorSecondary(uint8 Value)
{
	ColorSecondary = Value;
}

void UCharacterCustomizationComponent::SetColorMetalPrimary(uint8 Value)
{
	ColorMetalPrimary = Value;
}

void UCharacterCustomizationComponent::SetColorMetalSecondary(uint8 Value)
{
	ColorMetalSecondary = Value;
}

void UCharacterCustomizationComponent::SetColorMetalDark(uint8 Value)
{
	ColorMetalDark = Value;
}

void UCharacterCustomizationComponent::SetColorLeatherPrimary(uint8 Value)
{
	ColorLeatherPrimary = Value;
}

void UCharacterCustomizationComponent::SetColorLeatherSecondary(uint8 Value)
{
	ColorLeatherSecondary = Value;
}

void UCharacterCustomizationComponent::SetColorHair(uint8 Value)
{
	ColorHair = Value;
}

void UCharacterCustomizationComponent::SetColorBodyArt(uint8 Value)
{
	ColorBodyArt = Value;
}


/*
void UCharacterCustomizationComponent::GenerateAllMaterials()
{

	//Get material instance from character
	ACharacterBase* Character = Cast<ACharacterBase>(GetOwner());
	UMaterialInstanceDynamic* MaterialInstance = Character->CreateMaterialInstance();
	//Set Material instance
	MaterialInstance->SetTextureParameterValue

(
    FName("Color_Skin"),
    UTexture * Value
) 
	//Call character function and pass it the instance


	SkeletalMesh.CreateDynamicMaterialInstance(
		    0,
    class UMaterialInterface * SourceMaterial,
    FName OptionalName
	);



	DynamicMaterial.

	if(ColorSkin){}
}*/


