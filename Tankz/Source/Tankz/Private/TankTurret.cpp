// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"


void UTankTurret::Rotate(float RelativeSpeed) {
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1); //Just to be sure :)
	float RotationChange = RelativeSpeed * MaxDegreePerS * FApp::GetDeltaTime();
	float NewRotation = this->RelativeRotation.Yaw + RotationChange;
	this->SetRelativeRotation(FRotator(0, NewRotation, 0)); //0, 0 for jaw and roll
}

