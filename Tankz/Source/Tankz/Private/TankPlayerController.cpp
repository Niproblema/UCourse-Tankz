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


ATank * ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}