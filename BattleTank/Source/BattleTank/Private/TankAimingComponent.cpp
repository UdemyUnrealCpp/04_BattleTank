// Fill out your copyright notice in the Description page of Project Settings.
#include "BattleTank.h"

#include "TankBarrel.h"

#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; //TODO should this really tick ?

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	this->m_barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float launchSpeed)
{
	if (m_barrel == nullptr)
		return;

	//UE_LOG(LogTemp, Warning, TEXT("TANK %s aiming at %s from %s"), *this->GetOwner()->GetName(), *(HitLocation.ToString()), *this->m_barrel->GetComponentLocation().ToString());
	//UE_LOG(LogTemp, Warning, TEXT("Firing at %f"), launchSpeed);

	FVector OutLaunchVelocity;
	FVector StartLocation = m_barrel->GetSocketLocation(FName("Projectile"));
	TArray<AActor*> ignoredActors = TArray<AActor*>();
	ignoredActors.Add(this->GetOwner());
	
	//this bug and gives a lot of no solution
	/*bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this, OutLaunchVelocity,
		StartLocation, HitLocation, launchSpeed,
		false, 0.0f, 0.0f,
		ESuggestProjVelocityTraceOption::TraceFullPath, FCollisionResponseParams::DefaultResponseParam,
		ignoredActors,
		true
	);*/

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this, OutLaunchVelocity,
		StartLocation, HitLocation, launchSpeed,
		false, 0.0f, 0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace // Paramater must be present to prevent bug
	);

	if (bHaveAimSolution)
	{
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		//UE_LOG(LogTemp, Warning, TEXT("Aiming at %s"), *AimDirection.ToString());
		MoveBarrelTowards(AimDirection);
		float Time = this->GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f : Aim solution found %s"), Time, *OutLaunchVelocity.ToString());
	}
	else
	{
		float Time = this->GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f : No Aim solution found"), Time);
	}

	//no solution found
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	//work out difference between current barrel rotation and aimdirection
	FRotator BarrelRotator = this->m_barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator : %s"), *AimAsRotator.ToString());

	FRotator DeltaRotator = AimAsRotator - BarrelRotator;	

	this->m_barrel->Elevate(DeltaRotator.Pitch);//TODO remove magic number
}

