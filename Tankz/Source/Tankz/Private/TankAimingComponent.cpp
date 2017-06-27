// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent() {
	//TODO Should this tick maybe?
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet) {
	if (BarrelToSet)
		Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret * TurretToSet) {
	if (TurretToSet)
		Turret = TurretToSet;
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {
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
//UE_LOG(LogTemp, Warning, TEXT("Barrel pointing at %s"), *AimDirection.ToString())

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;
	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection) {
	FRotator TurretRotator = Turret->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();

	float DeltaRotation = AimAsRotator.Yaw - TurretRotator.Yaw + 360;
	DeltaRotation = fmodf(DeltaRotation, 360);
	DeltaRotation = DeltaRotation > 180 ? DeltaRotation - 360 : DeltaRotation;

	Turret->Rotate(DeltaRotation);
}
