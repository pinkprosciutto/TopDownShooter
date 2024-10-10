// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_FlockingAI.h"

// Sets default values for this component's properties
UAC_FlockingAI::UAC_FlockingAI()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UAC_FlockingAI::BeginPlay()
{
	Super::BeginPlay();
	ownerActor = GetOwner();
}

int UAC_FlockingAI::GetFlockID()
{
	return flockID;
}

// Called every frame
void UAC_FlockingAI::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

TArray<AActor*> UAC_FlockingAI::GetFlockingGroup()
{
	return flockingGroup;
}

void UAC_FlockingAI::InitiateFlock(FVector origin, int setFlockID, int flockSize, TArray<AActor*> flockingBuddy, float height)
{
	flockID = setFlockID;
	flockingGroup = flockingBuddy;
	flockVelocity = ownerActor->GetActorForwardVector();
	flockVelocity.Normalize();
	flockVelocity *= FMath::FRandRange(minSpeed, maxSpeed);
	flockingCount = flockSize;
	
	//Randomize spawn spot
	currentRotation = ownerActor->GetActorRotation();

	const int32 randomSeed = FMath::RandRange(1, 1000);

	FRandomStream rand(randomSeed);
	float random = rand.FRandRange(0, 1);

	float alpha = 2 * 3.14f * random;

	float radius = spawnRadius * FMath::Sqrt(random);

	float X = radius * FMath::Cos(alpha); 
	float Y = radius * FMath::Sin(alpha); 

	FVector newLocation = FVector(X * flockSize * flockingDensity + origin.X, Y * flockSize * flockingDensity + origin.Y, height);

	GetOwner()->SetActorLocation(newLocation);

	/*if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%i %f %f"), flockSize, newLocation.Y, random));*/
}

void UAC_FlockingAI::UpdateRotation() {
	currentRotation = FMath::RInterpTo(currentRotation, ownerActor->GetActorRotation(), GetWorld()->DeltaTimeSeconds, 7.0f);
	ownerActor->SetActorRotation(currentRotation);
}

FVector UAC_FlockingAI::Separate() {
	
	FVector steering = FVector::ZeroVector;
	FVector SeparationDirection = FVector::ZeroVector;
	int flockCount = 0;
	float proximityFactor = 0.0f;

	//get separation steering force for each of the actor's flockmates

	for (AActor* flockingBuddy : flockingGroup)
	{
		//get normalized direction away from nearby flockmate
		SeparationDirection = ownerActor->GetActorLocation() - flockingBuddy->GetActorLocation();
		SeparationDirection = SeparationDirection.GetSafeNormal();

		//get scaling factor based off other actor's proximity. 0 = very far away (no separation force) & 1 = very close (full separation force)
		proximityFactor = 1.0f - (SeparationDirection.Size() / perceptionSphereRadius);

		//check if flockmate's center of mass is outside radius 
		if (proximityFactor < 0.0f)
		{
			continue;	
		}

		//add steering force of flockmate and increase flock count
		steering += (proximityFactor * SeparationDirection);
		flockCount++;

	}

	if (flockCount > 0)
	{
		//get flock average separation steering force, apply separation steering strength factor and return force
		steering /= flockingCount;
		steering.GetSafeNormal() -= flockVelocity.GetSafeNormal();
		steering *= separationStrength;
		return steering;
	}
	else
	{
		return FVector::ZeroVector;
	}

}

FVector UAC_FlockingAI::Align() {

	FVector steering = FVector::ZeroVector;
	int flockCount = 0;

	//get alignment steering force for each of the actor's flockmates
	for (AActor* flockingBuddy : flockingGroup)
	{
		UAC_FlockingAI* flockComponent = flockingBuddy->GetComponentByClass<UAC_FlockingAI>();
		
		//add flockmate's alignment force
		steering += flockComponent->flockVelocity.GetSafeNormal();
		flockCount++;
	}

	if (flockCount > 0)
	{
		//get alignment force to average flock direction
		steering /= flockCount;
		steering.GetSafeNormal() -= flockVelocity.GetSafeNormal();
		steering *= alignmentStrength;
		return steering;
	}
	else
	{
		return FVector::ZeroVector;
	}
}

FVector UAC_FlockingAI::GroupUp() {

	FVector steering = FVector::ZeroVector;
	int flockCount = 0;
	FVector averagePosition = FVector::ZeroVector;

	//get sum of flockmate positions
	for (AActor* flockingBuddy : flockingGroup)
	{
		//get cohesive force to group with flockmate
		averagePosition += flockingBuddy->GetActorLocation();
		flockCount++;
	}

	if (flockCount > 0)
	{
		//average cohesion force of flock
		averagePosition /= flockCount;
		steering = averagePosition - ownerActor->GetActorLocation();
		steering.GetSafeNormal() -= flockVelocity.GetSafeNormal();
		steering *= cohesionStrength;
		return steering;
	}
	else
	{
		return FVector::ZeroVector;
	}
}

void UAC_FlockingAI::Steer(FVector targetActorLocation, TArray<TEnumAsByte<EObjectTypeQuery>> obstacleCheck, bool drawDebug, float deltaTime) {

	FVector acceleration = FVector::ZeroVector;

	//update position and rotation
	ownerActor->SetActorLocation(ownerActor->GetActorLocation() + (flockVelocity * deltaTime));
	ownerActor->SetActorRotation(flockVelocity.ToOrientationQuat());

	//apply steering forces to acceleration
	acceleration += Separate();
	acceleration += Align();
	acceleration += GroupUp();

	FVector currentLocation = FVector(ownerActor->GetActorLocation().X, ownerActor->GetActorLocation().Y, 0);
	FVector targetLocation = FVector(targetActorLocation.X, targetActorLocation.Y, 0);

	acceleration += ((targetLocation - currentLocation) * targetChaseMultiplier);
	
	//update velocity
	flockVelocity += (acceleration * deltaTime);
	flockVelocity = flockVelocity.GetClampedToSize(minSpeed, maxSpeed);
}

void UAC_FlockingAI::SetFlockingCount(int flockCount) {
	flockingCount = flockCount;
}

void UAC_FlockingAI::GetCurrentFlockingCount(int& flockCount) {
	flockCount = flockingCount;
}