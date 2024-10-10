// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AC_ObjectPool.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPoolReturned, AActor*, actor);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNSHOOTER_API UAC_ObjectPool : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_ObjectPool();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	TArray<AActor*> ObjectPool;
	TArray<bool> ActiveObjects;
	int currentIndex;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, category = "ObjectPool")
	void SpawnPool(AActor* Owner, TArray<AActor*> &SpawnedObjects);

	UFUNCTION(BlueprintCallable, category = "ObjectPool")
	void ActivateObject(FVector location, FRotator rotation, AActor* &activatedActor);

	UFUNCTION(BlueprintCallable, category = "ObjectPool")
	void DeactivateObject(int objectIndex);

	UPROPERTY(EditAnywhere, category = "ObjectPool")
	TSubclassOf<class AActor> PooledActor;

	UPROPERTY(EditAnywhere, category = "ObjectPool")
	int PoolSize;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, category = "ObjectPool")
	FPoolReturned PoolReturned;
};
