// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IBP_Weapon.h"
#include "Weapon.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDamage, const TArray <FHitResult>&, HitResults);

UCLASS()
class TOPDOWNSHOOTER_API AWeapon : public AActor, public IIBP_Weapon
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	AActor* PooledProjectile;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnFire_Implementation() override;

	virtual void OnRelease_Implementation() override;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, category = "Weapon")
	FOnDamage OnDamage;
};
