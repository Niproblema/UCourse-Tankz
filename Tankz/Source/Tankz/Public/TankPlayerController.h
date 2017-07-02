// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include "TankPlayerController.generated.h" //Must be last include


class ATank;
class UTankAimingComponent;

UCLASS()
class TANKZ_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()


public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION(BlueprintCallable, Category = Setup)
		ATank * GetControlledTank() const;
	UFUNCTION(BlueprintImplementableEvent, Category = Setup)
		void FoundAimingComponent(UTankAimingComponent * AimCompRef);

private:

	void AimTowardsCrosshair(); //Aim so shot hits the crosshair location
	bool GetSightRayHitLocation(FVector & HitLocation) const; //Raycast though the dot. If it hits, return true. Also OutParameter

	UPROPERTY(EditAnywhere)
		float CrosshairXShare = 0.5f;
	UPROPERTY(EditAnywhere)
		float CrosshairYShare = 0.4f;
	UPROPERTY(EditAnywhere)
		float RayTraceDistance = 1000000.f;
};
