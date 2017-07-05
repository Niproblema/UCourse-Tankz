// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent() {
	//TODO Should this tick maybe?
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay() {
	//Begins lel
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (AmmoLeft <= 0) {
		FiringState = EFiringState::OutOfAmmo;
	}else if (ReloadTimeS >= (FPlatformTime::Seconds() - LastFireTime)) {
		FiringState = EFiringState::Reloading;
	} else if (!isLocked()){
		FiringState = EFiringState::Aiming;
	} else {
		FiringState = EFiringState::Locked;
	}
}

void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet) {
	Barrel = BarrelToSet;
	Turret = TurretToSet;	
}

EFiringState UTankAimingComponent::GetFiringState() const {
	return FiringState;
}

int32 UTankAimingComponent::GetAmmo() const {
	return AmmoLeft;
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
			AimDirection = OutLaunchVelocity.GetSafeNormal();
			MoveTurretTowards(AimDirection);
			MoveBarrelTowards(AimDirection);
		}
		else {
			float Tajm = GetWorld()->GetTimeSeconds();
			//UE_LOG(LogTemp, Error, TEXT("%f: SomethingWrong AimingComponent AimAt()"), Tajm);
			//Means that no solution to target has been found!
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

bool UTankAimingComponent::isLocked() {
	//TODO HitLocation == TargetTank ? return true : false; //AutoAim Ability
	if (!ensure(Barrel)) return false;
	FVector BarrelOrientation = Barrel->GetForwardVector();
	return BarrelOrientation.Equals(AimDirection, 0.01);
}

void UTankAimingComponent::Shoot() {
	if ((FiringState == EFiringState::Reloading) || (FiringState == EFiringState::OutOfAmmo) || !ensure(Barrel && ProjectileBP)) return;
	AProjectile * NewProjectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileBP,
		Barrel->GetSocketLocation(FName("OutHole")),
		Barrel->GetForwardVector().Rotation()
		);
	LastFireTime = FPlatformTime::Seconds();
	NewProjectile->LaunchProjectile(LaunchSpeed);
	AmmoLeft--;
}


