// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATank::SetBarrelReference(UTankBarrel * BarrelToSet){
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret * TurretToSet) {
	TankAimingComponent->SetTurretReference(TurretToSet);
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector HitLocation){
	if (TankAimingComponent) {
		TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
	}else
		UE_LOG(LogTemp, Error, TEXT("No Aiming component found!"))
}

void ATank::Shoot() {
	bool isReloaded = ReloadTimeS <= (FPlatformTime::Seconds()- LastFireTime);

	if (!Barrel || !isReloaded) return;

	AProjectile * NewProjectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileBP,
		Barrel->GetSocketLocation(FName("OutHole")),
		Barrel->GetForwardVector().Rotation()
		);
	LastFireTime = FPlatformTime::Seconds();
	NewProjectile->LaunchProjectile(LaunchSpeed);

}
