// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_ObjectPool.h"
#include "IBP_PoolableObject.h"
#include "Projectile.h"

// Sets default values for this component's properties
UAC_ObjectPool::UAC_ObjectPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAC_ObjectPool::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAC_ObjectPool::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAC_ObjectPool::SpawnPool(AActor* Owner, TArray<AActor*>& SpawnedObjects)
{
	UWorld* World = GetWorld();

	//AActor* SpawnedActor = World->SpawnActor<AActor>(PooledActor, FVector().ZeroVector, FRotator().ZeroRotator);
	for (int i = 0; i < PoolSize; i++) {

		AActor* SpawnedActor = World->SpawnActor<AActor>(PooledActor, FVector().ZeroVector, FRotator().ZeroRotator);
	
		IIBP_PoolableObject* ActorInterface = Cast<IIBP_PoolableObject>(SpawnedActor);

		ActorInterface->Execute_InitializeObject(SpawnedActor, this, i, GetOwner());

		ObjectPool.Add(SpawnedActor);
		ActiveObjects.Add(false);
	}

	SpawnedObjects = ObjectPool;
}

void UAC_ObjectPool::ActivateObject(FVector location, FRotator rotation, AActor* &activatedActor)
{
	//Terminate function if the array is null, prevent crashing
	if (ObjectPool[currentIndex] == nullptr) {
		currentIndex = 0;
		return;
	}

	if (!ActiveObjects[currentIndex]) {
		IIBP_PoolableObject* ActorInterface = Cast<IIBP_PoolableObject>(ObjectPool[currentIndex]);
		//if (ActorInterface == nullptr) return;
		ActorInterface->Execute_OnActivate(ObjectPool[currentIndex], location, rotation);
		ActiveObjects[currentIndex] = true;
		activatedActor = ObjectPool[currentIndex];
	}

	currentIndex++;

	if (currentIndex >= PoolSize) 
		currentIndex = 0;
}

void UAC_ObjectPool::DeactivateObject(int objectIndex)
{
	ActiveObjects[objectIndex] = false;
	IIBP_PoolableObject* ActorInterface = Cast<IIBP_PoolableObject>(ObjectPool[objectIndex]);
	ActorInterface->Execute_OnDeactivate(ObjectPool[objectIndex]);
	PoolReturned.Broadcast(ObjectPool[objectIndex]);
}

