// Copyright Creating Mountains!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RaidingBoatActor.generated.h"

class ACharacterBase;
UCLASS()
class NORTHERNCAMP_API ARaidingBoatActor : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARaidingBoatActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Boat Settings")
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Boat Settings")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boat Settings")
	float BoatSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boat Settings")
	float MaxRadiusDisambarkSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boat Settings")
	float BoatHeightFalling;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boat Settings")
	float TimeBeforeDisembarking;

	FTimerHandle DisembarkTimerHandle; 

	void AttachRaiders(TArray<ACharacterBase*> RaidersToAttach);

	UFUNCTION()
	void Disembark();

	FVector TargetLocation;
	bool StartMoving = false;
	bool bSetupCompleted = false;

	//Variables
	int32 NumberOfSeats = 0;
	bool bCanDisembark = false;
	
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	void SetupMoveCoordinations();
	


	//Variables 
	FVector Direction;
	float TotalDistance;
	float CurrentDistance;
	FVector StartLocation;
	bool bEveryonesOut;
	

	TArray<ACharacterBase*> RaidersOnBoat;

	


};
