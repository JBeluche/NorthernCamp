// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Runtime/Engine/Classes/Materials/Material.h"
#include "CharacterCustomizationComponent.generated.h"



USTRUCT(BlueprintType)
struct NORTHERNCAMP_API FStructColorParams
{
	GENERATED_BODY()

	//Color Values for the character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skin Colors")
	TArray <FLinearColor> SkinColorsArray;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skin Colors")
	TArray <FLinearColor> PrimaryColorArray;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skin Colors")
	TArray <FLinearColor> SecondaryColorArray;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skin Colors")
	TArray <FLinearColor> MetalSecondaryColorArray;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skin Colors")
	TArray <FLinearColor> MetalPrimaryColorArray;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skin Colors")
	TArray <FLinearColor> MetalDarkColorArray;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skin Colors")
	TArray <FLinearColor> LeatherPrimaryColorArray;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skin Colors")
	TArray <FLinearColor> LeatherSecondaryColorArray;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skin Colors")
	TArray <FLinearColor> BodyArtColorArray;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skin Colors")
	TArray <FLinearColor> HairColorArray;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skin Colors")
	TArray <FLinearColor> StubbleColorArray;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skin Colors")
	TArray <FLinearColor> ScarColorArray;
};



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NORTHERNCAMP_API UCharacterCustomizationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterCustomizationComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	TArray<USkeletalMesh*> MeshesToMerge;

public:	

//Skeleton to set
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts")
	USkeleton* Skeleton;

//Body parts
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts")
	USkeletalMesh* Head;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts")
	USkeletalMesh* Eyebrows;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts")
	USkeletalMesh* FacialHair;
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts")
	USkeletalMesh* Torso;
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts")
	USkeletalMesh* ArmUpperRight;
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts")
	USkeletalMesh* ArmUpperLeft;
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts")
	USkeletalMesh* ArmLowerRight;
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts")
	USkeletalMesh* ArmLowerLeft;
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts")
	USkeletalMesh* HandRight;
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts")
	USkeletalMesh* HandLeft;
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts")
	USkeletalMesh* Hips;
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts")
	USkeletalMesh* LegRight;
		
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts")
	USkeletalMesh* LegLeft;
		
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts")
	USkeletalMesh* Hair;

	//Attachments

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attachments")
	USkeletalMesh* HeadAttachmentHair;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attachments")
	USkeletalMesh* HeadAttachmentHelmet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attachments")
	USkeletalMesh* ChestAttachment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attachments")
	USkeletalMesh* HeadCoveringsBaseHair;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attachments")
	USkeletalMesh* HeadCoveringsNoHair;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attachments")
	USkeletalMesh* HeadCoveringsNoFacialHair;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attachments")
	USkeletalMesh* BackAttachment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attachments")
	USkeletalMesh* ShoulderAttachmentRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attachments")
	USkeletalMesh* ShoulderAttachmentLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attachments")
	USkeletalMesh* ElbowAttachmentRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attachments")
	USkeletalMesh* ElbowAttachmentLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attachments")
	USkeletalMesh* HipAttachment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attachments")
	USkeletalMesh* KneeAttachmentRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attachments")
	USkeletalMesh* KneeAttachmentLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attachments")
	USkeletalMesh* Extras;

	//Material settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Settings")
	UMaterialInstanceDynamic* DynamicMaterial;

	UMaterialInterface* MainMaterial;
	UMaterialInterface* MaskMaterial;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Settings")
	uint8 ColorSkin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Settings")
	uint8 ColorPrimary;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Settings")
	uint8 ColorSecondary;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Settings")
	uint8 ColorMetalPrimary;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Settings")
	uint8 ColorMetalSecondary;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Settings")
	uint8 ColorMetalDark;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Settings")
	uint8 ColorLeatherPrimary;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Settings")
	uint8 ColorLeatherSecondary;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Settings")
	uint8 ColorHair;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Settings")
	uint8 ColorBodyArt;

	//Linear colors
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Settings")
	FLinearColor LinearColorSkin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Settings")
	FLinearColor LinearColorPrimary;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Settings")
	FLinearColor LinearColorSecondary;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Settings")
	FLinearColor LinearColorMetalPrimary;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Settings")
	FLinearColor LinearColorMetalSecondary;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Settings")
	FLinearColor LinearColorMetalDark;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Settings")
	FLinearColor LinearColorLeatherPrimary;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Settings")
	FLinearColor LinearColorLeatherSecondary;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Settings")
	FLinearColor LinearColorHair;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Settings")
	FLinearColor LinearColorBodyArt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Settings")
	FLinearColor LinearColorStubble;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Settings")
	FLinearColor LinearColorScar;

	//Functions
	UFUNCTION(BlueprintCallable, Category = "Mesh Merge")
	TArray<USkeletalMesh*> GetAllMeshesToMerge();

	UFUNCTION(BlueprintCallable, Category = "Mesh Merge")
	void GenerateAllMaterials();

	/*void SetColorSkin(uint8 Value);
	void SetColorPrimary(uint8 Value);
	void SetColorSecondary(uint8 Value);
	void SetColorMetalPrimary(uint8 Value);
	void SetColorMetalSecondary(uint8 Value);
	void SetColorMetalDark(uint8 Value);
	void SetColorLeatherPrimary(uint8 Value);
	void SetColorLeatherSecondary(uint8 Value);
	void SetColorHair(uint8 Value);
	void SetColorBodyArt(uint8 Value);*/

};
