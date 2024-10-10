// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IBP_PoolableObject.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIBP_PoolableObject : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TOPDOWNSHOOTER_API IIBP_PoolableObject
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, category = "ObjectPool")
	void InitializeObject(UAC_ObjectPool* objectPool, int index, AActor* owner);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, category = "ObjectPool")
	void OnActivate(FVector position, FRotator rotation);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, category = "ObjectPool")
	void OnDeactivate();

};
