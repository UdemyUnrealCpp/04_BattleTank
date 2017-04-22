// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float CrosshairXLocation = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float CrosshairYLocation = 1.0f / 3.0f;
	
	
private:

	virtual void BeginPlay() override;
	virtual void Tick(float fDeltaTime) override;

	ATank* GetControlledTank() const;

	//Start the tank moving the barrel so that a shot would hit where
	//the crosshair intersects the world
	void AimTowardsCrosshair();

	//return OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector &outHitLocation) const;
	//deproject the screen position of the crosshair to a world direction
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	
	
};
