// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GameFramework/Actor.h"
#include "TankAiController.generated.h"

class ATank;

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

	ATank *  TargetTank;
	ATank * ControlledTank;

	UPROPERTY(EditAnywhere)
		float RayTraceDistance = 1000000.f;

	UPROPERTY(EditAnywhere)
		float AcceptanceRadius = 1500;
};
