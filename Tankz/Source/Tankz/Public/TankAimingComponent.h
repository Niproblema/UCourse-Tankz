// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SceneComponent.h"
#include "Math/Vector.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "TankAimingComponent.generated.h"

//Enums for crosshair colors

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

//Forward Declaration
class UTankBarrel;
class UTankTurret;


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKZ_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Setup)
		void Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet);

	void AimAt(FVector HitLocation, float LaunchSpeed);

protected:
	UPROPERTY(BlueprintReadOnly, Category = State)
		EFiringState FiringState = EFiringState::Locked;
private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	void MoveBarrelTowards(FVector AimDirection);
	void MoveTurretTowards(FVector AimDirection);

	UTankBarrel * Barrel = nullptr;
	UTankTurret * Turret = nullptr;


};
