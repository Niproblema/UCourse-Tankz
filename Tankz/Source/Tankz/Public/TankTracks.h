// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Misc/App.h"
#include "Components/StaticMeshComponent.h"
#include "TankTracks.generated.h"

/**
 * TankTracks.h - One for each track, can't change name anymore :(
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKZ_API UTankTracks : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	//[-1,1]
	UFUNCTION(BlueprintCallable, Category = Input)
		void SetThrottle(float Throttle);

private:
	UTankTracks();
	virtual void BeginPlay() override;
	void ApplySidewaysForce(float);
	void DriveTrack();

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	//MaxForcePerTrack in newtons
	UPROPERTY(EditAnywhere, Category = Setup)
		float TrackMaxDrivingForce = 30000000;

	UPROPERTY(EditAnywhere, Category = Setup)
		float DriftFactor = 100; //Higher = more Drift

	float CurrentThrottle = 0;

};
