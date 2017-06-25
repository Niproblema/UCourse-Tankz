// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class TANKZ_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float DegreesPerSecond);
	
private:
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreePerS = 20.f;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreeUP = 40.f;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreeDOWN= -1.f;
	
};
