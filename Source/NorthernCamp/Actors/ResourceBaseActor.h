// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ResourceBaseActor.generated.h"

UCLASS()
class NORTHERNCAMP_API AResourceBaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResourceBaseActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* SceneComponent;

};
