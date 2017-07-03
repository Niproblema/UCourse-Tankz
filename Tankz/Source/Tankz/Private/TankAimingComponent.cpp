// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent() {
	//TODO Should this tick maybe?
}

void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet) {
	Barrel = BarrelToSet;
	Turret = TurretToSet;	
}



void UTankAimingComponent::AimAt(FVector HitLocation) {
	if (Barrel && Turret) {
		FVector OutLaunchVelocity;
		FVector StartLocation = Barrel->GetSocketLocation(FName("OutHole"));
		if (UGameplayStatics::SuggestProjectileVelocity(
			this,
			OutLaunchVelocity,
			StartLocation,
			HitLocation,
			LaunchSpeed,
			false,
			0,
			0,
			ESuggestProjVelocityTraceOption::DoNotTrace
		)) {	//Found AimSolution and determined AimDirection. Next rotate barrel!		
			FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
			MoveTurretTowards(AimDirection);
			MoveBarrelTowards(AimDirection);
		}
		else {
			float Tajm = GetWorld()->GetTimeSeconds();
			UE_LOG(LogTemp, Error, TEXT("%f: SomethingWrong AimingComponent AimAt()"), Tajm);

			//Do nothing for now.
		}
	}
	return;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	if (!Barrel) return;

	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;
	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection) {
	if (!Turret) return;

	FRotator TurretRotator = Turret->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();

	float DeltaRotation = AimAsRotator.Yaw - TurretRotator.Yaw + 360;
	DeltaRotation = fmodf(DeltaRotation, 360);
	DeltaRotation = DeltaRotation > 180 ? DeltaRotation - 360 : DeltaRotation;

	Turret->Rotate(DeltaRotation);
}

void UTankAimingComponent::Shoot() {
	bool isReloaded = ReloadTimeS <= (FPlatformTime::Seconds() - LastFireTime);

	if (!ensure(Barrel && ProjectileBP) || !isReloaded) return;

	AProjectile * NewProjectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileBP,
		Barrel->GetSocketLocation(FName("OutHole")),
		Barrel->GetForwardVector().Rotation()
		);
	LastFireTime = FPlatformTime::Seconds();
	NewProjectile->LaunchProjectile(LaunchSpeed);
}
