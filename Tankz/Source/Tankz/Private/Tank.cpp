// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

// Sets default values
ATank::ATank() {
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay() {
	Super::BeginPlay();
	CurrentHealth = StartingHealth;
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser) {
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	int32 DamageToApply = FMath::Clamp(FPlatformMath::RoundToInt(ActualDamage), 0, CurrentHealth);
	//UE_LOG(LogTemp, Warning, TEXT("TOOK %d DAMAGE"), DamageToApply);

	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0) {
		OnDeath.Broadcast();
		//UE_LOG(LogTemp, Warning, TEXT("TANK DEDD"), );
	}
	return DamageToApply;
}

float ATank::GetHealthPercent() const {
	return (float)CurrentHealth / (float)StartingHealth;
}
