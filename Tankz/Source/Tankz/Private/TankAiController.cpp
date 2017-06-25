// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAiController.h"

void ATankAiController::BeginPlay() {
	Super::BeginPlay();
	ATank * ControlledTank = GetControlledTank();

	if (ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("AiControler reporting from %s!"), *(ControlledTank->GetName()))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AiControler BeginPlay NO TANK CONTROLLED!"))
	}

	TargetTank = GetPlayerTank();
	if (TargetTank) {
		UE_LOG(LogTemp, Warning, TEXT("AiControler Found target %s!"), *(TargetTank->GetName()))
	}else
		UE_LOG(LogTemp, Warning, TEXT("AiControler No Target found!"))
}

void ATankAiController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankAiController::AimTowardsCrosshair() {
	if (!GetControlledTank() || !TargetTank)return;
	FVector TargetingForLocation = TargetTank->GetActorLocation();
	GetControlledTank()->AimAt(TargetingForLocation);
}

ATank * ATankAiController::GetPlayerTank() const {
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}


ATank * ATankAiController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}