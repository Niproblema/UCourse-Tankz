// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAiController.h"
#include "Tank.h"
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

	if (AimingComponent->GetFiringState() == EFiringState::Locked) {
		AimingComponent->Shoot();
	}
}

void ATankAiController::SetPawn(APawn * InPawn) {
	Super::SetPawn(InPawn);
	if (InPawn) {
		ATank * PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) return;

		//Subscribe to Tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAiController::OnPossessedTankDeath);
	}
}

void ATankAiController::OnPossessedTankDeath() {
	if (!GetPawn()) { return; } //?
	GetPawn()->DetachFromControllerPendingDestroy();
}
