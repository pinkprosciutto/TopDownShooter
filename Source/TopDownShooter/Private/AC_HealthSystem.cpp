// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_HealthSystem.h"

// Sets default values for this component's properties
UAC_HealthSystem::UAC_HealthSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAC_HealthSystem::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAC_HealthSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAC_HealthSystem::InitializeHealth(float health)
{
	maxHP = health;
	currentHP = health;
}

void UAC_HealthSystem::GetCurrentHealth(float &currentHealth, float &maxHealth)
{
	currentHealth = currentHP;
	maxHealth = maxHP;
}

void UAC_HealthSystem::TakeDamage(float damage, AActor* damageCauser)
{
	currentHP -= (damage * damageModifier);
	if (currentHP <= 0.0f) {
		Death.Broadcast();
	}
}

void UAC_HealthSystem::SetDamageModifier(float newValue)
{
	damageModifier = newValue;
}

void UAC_HealthSystem::SetCurrentHealth(float newValue)
{
	currentHP = newValue;
}

void UAC_HealthSystem::GetDamageModifier(float &value)
{
	value = damageModifier;
}
