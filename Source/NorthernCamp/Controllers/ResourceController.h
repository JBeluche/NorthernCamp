// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ResourceController.generated.h"

UENUM(BlueprintType)
enum class EResourceType : uint8 
{
	None UMETA(DisplayName = "None"),
	Water UMETA(DisplayName = "Water"),
	Food UMETA(DisplayName = "Food"),
	Wood UMETA(DisplayName = "Wood"),

};

USTRUCT(BlueprintType)
struct FResourceTypeInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource Settings")
	FSlateBrush ResouceIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource Settings")
	FText DisplayName;
};

UCLASS()
class NORTHERNCAMP_API AResourceController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResourceController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource Settings")
	TMap<EResourceType, FResourceTypeInfo> ResourcesInfoMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource Settings")
	TArray<EResourceType> GatherableResources;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
