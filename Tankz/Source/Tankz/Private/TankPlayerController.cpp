// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"



void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	ATank * ControlledTank = GetControlledTank();

	if (ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerControler BeginPlay with %s"), *(ControlledTank->GetName()))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerControler BeginPlay NO TANK CONTROLLED!"))
	}

}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
	//Aim at someone

}


ATank * ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetControlledTank())return;
	FVector TargetingForLocation; //OUT Parameter
	if (GetSightRayHitLocation(TargetingForLocation)) {
		GetControlledTank()->AimAt(TargetingForLocation);
		
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
			ECollisionChannel::ECC_Visibility
		)){
			OutHitLocation = HitResult.Location;
			return true;
		}
	}
	OutHitLocation = FVector(0);
	return false;
}
