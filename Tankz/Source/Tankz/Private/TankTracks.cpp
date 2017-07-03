// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTracks.h"

UTankTracks::UTankTracks() {
	PrimaryComponentTick.bCanEverTick = false;;
}

void UTankTracks::BeginPlay() {
	OnComponentHit.AddDynamic(this, &UTankTracks::OnHit);
}

void UTankTracks::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	ApplySidewaysForce(DriftFactor);
	DriveTrack();
	CurrentThrottle = 0;
}

void UTankTracks::SetThrottle(float Throttle) {
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTracks::DriveTrack() {
	FVector ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent * TankPC = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankPC->AddForceAtLocation(ForceApplied, ForceLocation);
}


void UTankTracks::ApplySidewaysForce(float Magnitude) {
	float RelativeSlippage = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	FVector SideDragAcceleration = (-RelativeSlippage * GetRightVector()) / (DeltaTime * Magnitude);
	UStaticMeshComponent * TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FVector CorrectionForce = TankRoot->GetMass() * SideDragAcceleration / 2;
	//TankRoot->AddForceAtLocation(CorrectionForce, GetComponentLocation());
	TankRoot->AddForce(CorrectionForce);
}

