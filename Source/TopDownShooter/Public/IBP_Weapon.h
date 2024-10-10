// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IBP_Weapon.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIBP_Weapon : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TOPDOWNSHOOTER_API IIBP_Weapon
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, category = "Weapon")
	void OnFire();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, category = "Weapon")
	void OnRelease();


};
