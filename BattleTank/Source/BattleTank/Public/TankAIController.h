// Fill out your copyright notice in the Description page of Project Settings.

#pragma once




#include "AIController.h"
#include "TankAIController.generated.h"


class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:

	virtual void BeginPlay() override;
	virtual void Tick(float fDeltaTime) override;

	ATank* GetControlledTank() const;
	ATank* GetPlayerTank() const;

	void AimTowardsTarget();

	ATank* Target;

	//How close can the AI tank get
	float AcceptanceRadius = 3000;
	
};
