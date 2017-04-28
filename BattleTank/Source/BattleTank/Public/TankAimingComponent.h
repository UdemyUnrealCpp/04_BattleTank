// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//forward declaration
class UTankBarrel; 

//Hold barrel's properties and Elevate Method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();


public:	

	void SetBarrelReference(UTankBarrel* BarrelToSet);

	//TODO add SetTurretReference();

	void AimAt(FVector HitLocation, float launchSpeed);


private:
	UTankBarrel* m_barrel = nullptr;

	void MoveBarrelTowards(FVector AimDirection);
	
};
