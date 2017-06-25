// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent() {
	// ...
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent * BarrelToSet) {
	Barrel = BarrelToSet;
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {
	if (Barrel) {
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
		)){	//Found AimSolution and determined AimDirection. Next rotate barrel!		
			FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
			UE_LOG(LogTemp, Warning, TEXT("Barrel pointing at %s"), *AimDirection.ToString())
			MoveBarrelTowards(AimDirection);
		}
		else{
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

	UE_LOG(LogTemp, Warning, TEXT("Barrel pointing at %s"), *DeltaRotator.ToString())
}