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
class AProjectile;


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKZ_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Setup)
		void Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet);

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void Shoot();

protected:
	UPROPERTY(BlueprintReadOnly, Category = State)
		EFiringState FiringState = EFiringState::Reloading;
private:
	// Sets default values for this component's properties
	UTankAimingComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void MoveBarrelTowards(FVector AimDirection);
	void MoveTurretTowards(FVector AimDirection);
	bool isLocked();

	UTankBarrel * Barrel = nullptr;
	UTankTurret * Turret = nullptr;
	FVector AimDirection;

	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 80000.f;
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float ReloadTimeS = 3;
	UPROPERTY(EditAnywhere, Category = Firing)
		TSubclassOf<AProjectile> ProjectileBP;
	double LastFireTime = FPlatformTime::Seconds();


};
