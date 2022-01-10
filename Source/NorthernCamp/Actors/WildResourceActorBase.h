// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "Components/ResourceManagerComponent.h"
#include "GameFramework/Actor.h"
#include "WildResourceActorBase.generated.h"

class UResourceManagerComponent;
enum class EResourceType : uint8;


UCLASS()
class NORTHERNCAMP_API AWildResourceActorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AWildResourceActorBase();

	UPROPERTY(EditAnywhere, Category = "Wild Resource Settings")
	EResourceType ResourceType;

	UPROPERTY(EditAnywhere, Category = "Wild Resource Settings")
	float ResourceAmount = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wild Resource Settings")
	bool bCanRespawn = true;

	
protected:
	virtual void BeginPlay() override;

	UResourceManagerComponent* ResourceManagerComp;
	USceneComponent* SceneComponent;


};
