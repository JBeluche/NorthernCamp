// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "WildResourceGenerator.generated.h"

class USphereComponent;
class AWildResourceActorBase;
UCLASS()
class NORTHERNCAMP_API AWildResourceGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	AWildResourceGenerator();

	UPROPERTY(EditAnywhere, Category = "Settings")
	USphereComponent* ActionArea;

	UPROPERTY(EditAnywhere, Category = "Settings")
	TMap<TSubclassOf<AWildResourceActorBase>, int32> WildResourcesToSpawn;
	
protected:
	virtual void BeginPlay() override;

	USceneComponent* SceneComponent;


};
