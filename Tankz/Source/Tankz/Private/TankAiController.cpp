// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAiController.h"
#include "TankAimingComponent.h"

void ATankAiController::BeginPlay() {
	Super::BeginPlay();
}

void ATankAiController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	APawn * ControlledTank = GetPawn();
	APawn * TargetTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	if (!ensure(ControlledTank && TargetTank))return;

	UTankAimingComponent * AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	MoveToActor(TargetTank, AcceptanceRadius);
	AimingComponent->AimAt(TargetTank->GetActorLocation());
	//AimingComponent->Shoot();
}
