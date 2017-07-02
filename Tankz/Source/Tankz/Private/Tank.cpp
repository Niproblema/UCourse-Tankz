// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
}

void ATank::AimAt(FVector HitLocation){
	if (TankAimingComponent) {
		TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
	}else
		UE_LOG(LogTemp, Error, TEXT("No Aiming component found! -Tank.cpp"))
}

void ATank::Shoot() {
	bool isReloaded = ReloadTimeS <= (FPlatformTime::Seconds()- LastFireTime);

	if (!ensure(Barrel) || !isReloaded) return;

	AProjectile * NewProjectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileBP,
		Barrel->GetSocketLocation(FName("OutHole")),
		Barrel->GetForwardVector().Rotation()
		);
	LastFireTime = FPlatformTime::Seconds();
	NewProjectile->LaunchProjectile(LaunchSpeed);

}
