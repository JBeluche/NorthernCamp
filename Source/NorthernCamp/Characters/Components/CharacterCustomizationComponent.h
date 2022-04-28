// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Runtime/Engine/Classes/Materials/Material.h"
#include "CharacterCustomizationComponent.generated.h"

class ACharacterBase;
UENUM()
enum class EArmorLevel : uint8 
{
	Level_0 UMETA(DisplayName = "No Armor"),
	Level_1 UMETA(DisplayName = "Leather 1 Armor"),
	Level_2 UMETA(DisplayName = "Leather 2 Armor"),
	Level_3 UMETA(DisplayName = "Leather 3 Armor"),
	Level_4 UMETA(DisplayName = "Iron 1 Armor"),
	Level_5 UMETA(DisplayName = "Iron 2 Armor"),
	Level_6 UMETA(DisplayName = "Iron 3 Armor"),
};

UENUM()
enum class EBodyType : uint8 
{
	PeasantLevel0 UMETA(DisplayName = "Peasant Body When Level 0"),
	CustomLevel0 UMETA(DisplayName = "Custom Body When Level 0"),
	CustomAllLevels UMETA(DisplayName = "The Character always has a custom body, doesnte use armor types"),

};

USTRUCT(BlueprintType)
struct FArmorMeshSet
{
	GENERATED_BODY()
	
	USkeletalMesh* Torso;
	USkeletalMesh* ArmUpperRight;
	USkeletalMesh* ArmUpperLeft;
	USkeletalMesh* ArmLowerRight;
	USkeletalMesh* ArmLowerLeft;
	USkeletalMesh* HandRight;
	USkeletalMesh* HandLeft;
	USkeletalMesh* Hips;
	USkeletalMesh* LegRight;
	USkeletalMesh* LegLeft;
	
};




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NORTHERNCAMP_API UCharacterCustomizationComponent : public UActorComponent
{
	GENERATED_BODY()
	
protected:
	
	// Called when the game starts
	virtual void BeginPlay() override;

	USkeletalMesh* SkeletalMeshBaseFemale;
	USkeletalMesh* SkeletalMeshBaseMale;

	
private:
	TArray<USkeletalMesh*> MeshesToMerge;

	ACharacterBase* Character;
	EArmorLevel CurrentArmorLevel = EArmorLevel::Level_0;
	
public:	
	// Sets default values for this component's properties
	UCharacterCustomizationComponent();
	void GenerateMeshes();
	void SetArmorLevel(EArmorLevel NewArmorLevel);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts")
	USkeleton* SkeletonToUse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts")
	USkeletalMesh* StaticBody;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts")
	EBodyType CharacterBodyType = EBodyType::CustomLevel0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts")
	bool bIsFemale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts")
	bool bHasCustomAnimation = false;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Parts")
	USkeletalMesh* ExtraHair;

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



};
