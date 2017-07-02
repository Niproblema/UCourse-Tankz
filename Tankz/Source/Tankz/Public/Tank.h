// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/UObjectGlobals.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "Tank.generated.h"

//Forward declarations
class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class AProjectile;

UCLASS()
class TANKZ_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void Shoot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent * TankAimingComponent = nullptr;


private:

	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 80000.f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float ReloadTimeS = 3;

	//Local barrel reference for spawning projectiles
	UTankBarrel * Barrel = nullptr;

	double LastFireTime = 0;

	UPROPERTY(EditAnywhere, Category = Firing)
		TSubclassOf<AProjectile> ProjectileBP;

};
