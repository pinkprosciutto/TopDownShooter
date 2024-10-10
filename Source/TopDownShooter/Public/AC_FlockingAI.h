// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AC_FlockingAI.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNSHOOTER_API UAC_FlockingAI : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_FlockingAI();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	int flockID = 0;
	TArray<AActor*> flockingGroup;
	TArray<FVector> targetingActorLocation;
	FRotator currentRotation;
	AActor* ownerActor;

	int flockingCount = 10;

	UPROPERTY(EditAnywhere, Category = "Flocking")
	int spawnRadius = 55;

	UPROPERTY(EditAnywhere, Category = "Flocking")
	float flockingDensity = 0.4f;

	UPROPERTY(EditAnywhere, Category = "Flocking")
	float minSpeed = 55.0f;

	UPROPERTY(EditAnywhere, Category = "Flocking")
	float maxSpeed = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Flocking")
	float separationStrength = 111.0f;

	UPROPERTY(EditAnywhere, Category = "Flocking")
	float alignmentStrength = 200.0f;

	UPROPERTY(EditAnywhere, Category = "Flocking")
	float cohesionStrength = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Flocking")
	float perceptionSphereRadius = 26.0f; //radius to check for nearby flockmates

	UPROPERTY(EditAnywhere, Category = "Flocking")
	float targetChaseMultiplier = 1.0f;

	void UpdateRotation();
	FVector Separate();
	FVector Align();
	FVector GroupUp();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Flocking")
	void InitiateFlock(FVector origin, int setFlockID, int flockSize, TArray<AActor*> flockingBuddy, float height);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Flocking")
	int GetFlockID();

	UFUNCTION(BlueprintCallable, Category = "Flocking")
	void SetFlockingCount(int flockCount);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Flocking")
	void GetCurrentFlockingCount(int& flockCount);

	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Flocking")
	TArray<AActor*> GetFlockingGroup();

	FVector flockVelocity;

	UFUNCTION(BlueprintCallable, Category = "Flocking")
	void Steer(FVector targetActorLocation,TArray<TEnumAsByte<EObjectTypeQuery>> obstacleCheck, bool drawDebug, float deltaTime);

};
