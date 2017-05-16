// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//enum for aiming state
UENUM()
enum class EFiringState : uint8
{
	EFiringStatus_LOCKED,
	EFiringStatus_AIMING,
	EFiringStatus_RELOADING,
};

//forward declaration
class UTankBarrel; 
class UTankTurret;

//Hold barrel's properties and Elevate Method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelReference(UTankBarrel* BarrelToSet);
	void SetTurretReference(UTankTurret* TurretToSet);

	void AimAt(FVector HitLocation, float launchSpeed);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringState m_eFiringStatus = EFiringState::EFiringStatus_RELOADING;


private:
	UTankBarrel* m_barrel = nullptr;
	UTankTurret* m_turret = nullptr;

	void MoveBarrelTowards(FVector AimDirection);
	void MoveTurretTowards(FVector AimDirection);
	
};
