// Fill out your copyright notice in the Description page of Project Settings.
#include "Projectile.h"
#include "IBP_PoolableObject.h"
// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetActorTickEnabled(false);
	SetActorHiddenInGame(true);

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::ActivateBullet_Implementation(FVector location, FRotator rotation)
{
	SetActorLocation(location, false);
	SetActorRotation(rotation);

	SetActorHiddenInGame(false);
	SetActorTickEnabled(true);

	//Set lifespan
	/*FTimerDelegate delegate; 
	delegate.BindUFunction(this, "DeactivateBullet"); 
	GetWorld()->GetTimerManager().SetTimer(lifespanHandler, delegate, Lifespan, false);*/
}

void AProjectile::DeactivateBullet_Implementation()
{
	/*GetWorld()->GetTimerManager().ClearTimer(lifespanHandler);*/

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

void AProjectile::MoveBullet_Implementation(float speed, float deltaTime)
{
	FVector location = GetActorLocation();

	location += GetActorForwardVector() * speed * deltaTime;

	SetActorLocation(location);
}

void AProjectile::OnBulletHit_Implementation(const TArray<FHitResult> &hitResult)
{


}

void AProjectile::CheckFrontActor(UPrimitiveComponent* socket, float distance, bool drawDebug, TArray<AActor*> IgnoredActors, TArray<TEnumAsByte<EObjectTypeQuery>> objectType, bool& isHit, TArray<FHitResult>& hitResult)
{
	FVector startLocation = socket->GetComponentLocation();
	FVector endLocation = startLocation + (socket->GetForwardVector() * distance);

	FCollisionQueryParams collisionParams;
	collisionParams.AddIgnoredActors(IgnoredActors);

	isHit = GetWorld()->LineTraceMultiByObjectType(hitResult, startLocation, endLocation, objectType, collisionParams);

	if (drawDebug) {
		FColor debugColor = isHit ? FColor::Red : FColor::Green;
		DrawDebugLine(GetWorld(), startLocation, endLocation, debugColor, false, .8f, 0, 1.0f);
	}
}

void AProjectile::CheckCollision(float radius, bool drawDebug, TArray<AActor*> IgnoredActors, TArray<TEnumAsByte<EObjectTypeQuery>> objectType, bool& isHit, TArray<FHitResult> &hitResult)
{
	FVector location = GetActorLocation();

	FCollisionShape sphere = FCollisionShape::MakeSphere(radius);

	FCollisionQueryParams collisionParams;
	collisionParams.AddIgnoredActors(IgnoredActors);

	isHit = GetWorld()->SweepMultiByObjectType(hitResult, location, location, FQuat::Identity, objectType, sphere, collisionParams);

	if (drawDebug) {
		FColor debugColor = isHit ? FColor::Red : FColor::Green;
		DrawDebugSphere(GetWorld(), location, radius, 1, debugColor, false, .8f, 0, 1.0f);
	}

}



void AProjectile::SetObjectLifespan(float lifespan)
{
	Lifespan = lifespan;
}


