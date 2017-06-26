// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent() {
	//TODO Should this tick maybe?
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet) {
	Barrel = BarrelToSet;
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {
	if (Barrel) {
		FVector OutLaunchVelocity;
		FVector StartLocation = Barrel->GetSocketLocation(FName("InHole"));
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

			//float Tajm = GetWorld()->GetTimeSeconds();
			//UE_LOG(LogTemp, Warning, TEXT("%f: Barrel pointing at %s"), Tajm, *AimDirection.ToString());

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