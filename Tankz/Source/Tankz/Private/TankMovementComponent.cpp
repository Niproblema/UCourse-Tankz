// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTracks.h"


void UTankMovementComponent::Initialise(UTankTracks * LeftOne, UTankTracks * RightOne) {
	LeftTrack = LeftOne;
	RightTrack = RightOne;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {
	//No super, we evil
	FVector TankDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();
	float ForwardThrow =  FVector::DotProduct(TankDirection, AIForwardIntention);


	FVector RightThrow = FVector::CrossProduct(AIForwardIntention, TankDirection); // .Z;
	float SteeringMagnitude = RightThrow.Size();
	float Steering = SteeringMagnitude*(fabsf(RightThrow.Z) / RightThrow.Z);

	IntendMoveForward(ForwardThrow);
	IntendMoveLeft(Steering);
}


void UTankMovementComponent::IntendMoveForward(float Throw) {
	if (!LeftTrack || !RightTrack) return;
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendMoveLeft(float Throw) {
	if (!LeftTrack || !RightTrack) return;
	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(Throw);
}