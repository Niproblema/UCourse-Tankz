// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent)) //opt: hidecategories = ("Collision")
class TANKZ_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	//[-1,1]
	void Rotate(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreePerS = 15;
	
	
	
};
