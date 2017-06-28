// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTracks.h"
#include "Tank.h"

void UTankTracks::SetThrottle(float Throttle) {
	//UE_LOG(LogTemp, Warning, TEXT("%s: %f"), *GetName() , Throttle);

	FVector ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent * TankPC = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankPC->AddForceAtLocation(ForceApplied, ForceLocation);
}


