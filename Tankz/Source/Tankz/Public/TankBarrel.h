// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Misc/App.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent)) //opt: hidecategories = ("Collision")
class TANKZ_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	//[-1,1]
	void Elevate(float RelativeSpeed);
	
private:
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreePerS = 15;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreeUP = 50;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreeDOWN= -1;
	
};
