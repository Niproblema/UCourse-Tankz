// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed) {
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1); //Just to be sure :)
	float ElevationChange = RelativeSpeed * MaxDegreePerS * FApp::GetDeltaTime();
	float NewElevation = RelativeRotation.Pitch + ElevationChange;

	NewElevation = FMath::Clamp<float>(NewElevation, MaxDegreeDOWN, MaxDegreeUP);
	this->SetRelativeRotation(FRotator(NewElevation, 0, 0)); //0, 0 for jaw and roll
}


