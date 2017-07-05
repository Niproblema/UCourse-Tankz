// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/Actor.h"
#include "Tank.generated.h"

UCLASS()
class TANKZ_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	//Called by the engine when projectile explodes nearby
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;
	
	//returns [0,1]
	UFUNCTION(BlueprintPure, Category = Health)
	float GetHealthPercent() const;

protected:

private:
	UPROPERTY(EditAnywhere, Category = Health)
		int32 StartingHealth = 100;
	UPROPERTY(VisibleAnywhere, Category = Health)
		int32 CurrentHealth = StartingHealth;


};
