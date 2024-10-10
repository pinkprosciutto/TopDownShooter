// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOPDOWNSHOOTER_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	float Lifespan;
	FTimerHandle lifespanHandler;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Projectile")
	void ActivateBullet(FVector location, FRotator rotation);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Projectile")
	void DeactivateBullet();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Projectile")
	void MoveBullet(float speed, float deltaTime);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Projectile")
	void OnBulletHit(const TArray<FHitResult> &hitResult);

	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void CheckFrontActor(UPrimitiveComponent* socket, float distance, bool drawDebug, TArray<AActor*> IgnoredActors, TArray<TEnumAsByte<EObjectTypeQuery>> objectType, bool &isHit, TArray<FHitResult> &hitResult);

	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void CheckCollision(float radius, bool drawDebug, TArray<AActor*> IgnoredActors, TArray<TEnumAsByte<EObjectTypeQuery>> objectType, bool& isHit, TArray<FHitResult> &hitResult);

	

	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void SetObjectLifespan(float lifespan);

};
