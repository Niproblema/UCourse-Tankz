// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "AIController.h"
#include "Engine.h"
#include "TankAiController.generated.h"

/**
 *
 */
UCLASS()
class TANKZ_API ATankAiController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	ATank * GetControlledTank() const;
	ATank * GetPlayerTank() const;
	void AimTowardsCrosshair();

	ATank *  TargetTank;
	UPROPERTY(EditAnywhere)
		float RayTraceDistance = 1000000.f;
};
