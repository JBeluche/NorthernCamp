// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NorthernCamp/Characters/CharacterBase.h"
#include "FactionBattleController.generated.h"

USTRUCT(BlueprintType)
struct FSquadInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Squad Information")
	int32 SquadNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Squad Information")
	ACharacterBase* SquadLeader;

	
};


UCLASS()
class NORTHERNCAMP_API AFactionBattleController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFactionBattleController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
