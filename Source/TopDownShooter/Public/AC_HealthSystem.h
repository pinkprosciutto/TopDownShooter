// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AC_HealthSystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeathDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnDamageDelegate, FVector, hitLocation, float, damage, AActor*, damageCauser);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNSHOOTER_API UAC_HealthSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_HealthSystem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	float currentHP;
	float maxHP;

	UPROPERTY(EditAnywhere, Category = "Health System")
	float damageModifier = 1.0f;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, category = "Health System")
	void InitializeHealth(float health);

	UFUNCTION(BlueprintCallable, BlueprintPure, category = "Health System")
	void GetCurrentHealth(float &currentHealth, float &maxHealth);

	UFUNCTION(BlueprintCallable, category = "Health System")
	void TakeDamage(float damage, AActor* damageCauser);

	UFUNCTION(BlueprintCallable, category = "Health System")
	void SetDamageModifier(float newValue);

	UFUNCTION(BlueprintCallable, category = "Health System")
	void SetCurrentHealth(float newValue);

	UFUNCTION(BlueprintPure, category = "Health System")
	void GetDamageModifier(float &value);

	UPROPERTY(BlueprintAssignable, BlueprintCallable, category = "Health System")
	FDeathDelegate Death;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, category = "Health System")
	FOnDamageDelegate OnDamage;

};
