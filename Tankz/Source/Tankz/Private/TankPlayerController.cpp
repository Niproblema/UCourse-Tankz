// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	UTankAimingComponent * AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) return;
	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
	//Aim at someone

}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetPawn()) return; //If not possesing
	UTankAimingComponent * AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) return;

	FVector TargetingForLocation; //OUT Parameter
	if (GetSightRayHitLocation(TargetingForLocation)) {
		AimingComponent->AimAt(TargetingForLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & OutHitLocation) const {
	int32 VSizeX, VSizeY;
	FVector CameraPosition, WorldDirection;
	GetViewportSize(VSizeX, VSizeY); //OUT Params
	FVector2D ScreenLocation = FVector2D(VSizeX * CrosshairXShare, VSizeY * CrosshairYShare);
	///Crosshair ray direction
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraPosition, WorldDirection)) {
		///RayTrace
		FHitResult HitResult;
		if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			CameraPosition,
			(CameraPosition + (WorldDirection * RayTraceDistance)),
			ECollisionChannel::ECC_Camera
		)) {
			OutHitLocation = HitResult.Location;
			return true;
		}
	}

	//float Tajm = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("%f: Player crosshair deprojection failed. Aiming at sky?"), Tajm);

	OutHitLocation = FVector(0);
	return false;
}
