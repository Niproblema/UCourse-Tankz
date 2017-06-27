// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAiController.h"
#include "Tank.h"

void ATankAiController::BeginPlay() {
	Super::BeginPlay();
	TargetTank = GetPlayerTank(); //Sets original tank to player!
	ControlledTank = GetControlledTank();
}

void ATankAiController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (!ControlledTank || !TargetTank)return;

	ControlledTank->AimAt(TargetTank->GetActorLocation());
	ControlledTank->Shoot();
}

ATank * ATankAiController::GetPlayerTank() const {
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}


ATank * ATankAiController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}