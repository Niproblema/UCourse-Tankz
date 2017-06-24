// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" //Must be last include

/**
 *
 */
UCLASS()
class TANKZ_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()


public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	ATank * GetControlledTank() const;
	void AimTowardsCrosshair(); //Aim so shot hits the crosshair location
	bool GetSightRayHitLocation(FVector & HitLocation) const; //Raycast though the dot. If it hits, return true. Also OutParameter

	UPROPERTY(EditAnywhere)
		float CrosshairXShare = 0.5f;
	UPROPERTY(EditAnywhere)
		float CrosshairYShare = 0.4f;
};
