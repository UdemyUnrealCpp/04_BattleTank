// Fill out your copyright notice in the Description page of Project Settings.
#include "BattleTank.h"

#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::Initialise(UTankBarrel* barrelToSet, UTankTurret* turretToSet)
{
	this->m_barrel = barrelToSet;
	this->m_turret = turretToSet;
}

void UTankAimingComponent::BeginPlay()
{
	this->m_lastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UE_LOG(LogTemp, Warning, TEXT("Tick Component"));

	if ((FPlatformTime::Seconds() - m_lastFireTime) > m_reloadTimeInSeconds)
	{
		this->m_eFiringState = EFiringState::EFiringStatus_RELOADING;
	}
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(m_barrel))
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
		StartLocation, HitLocation, this->m_launchSpeed,
		false, 0.0f, 0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace // Paramater must be present to prevent bug
	);

	if (bHaveAimSolution)
	{
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		//UE_LOG(LogTemp, Warning, TEXT("Aiming at %s"), *AimDirection.ToString());
		MoveBarrelTowards(AimDirection);
		MoveTurretTowards(AimDirection);
		float Time = this->GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f : Aim solution found %s"), Time, *OutLaunchVelocity.ToString());
	}
	else
	{
		float Time = this->GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f : No Aim solution found"), Time);
	}

	//no solution found
}

void UTankAimingComponent::Fire()
{
	if (this->m_eFiringState != EFiringState::EFiringStatus_RELOADING)
	{
		//UE_LOG(LogTemp, Warning, TEXT("%f TANK Fire"), this->GetWorld()->GetTimeSeconds());

		if(!ensure(this->m_barrel)) { return; }

		if(!ensure(this->m_projectileBlueprint)) { return; }

		FVector StartLocation = this->m_barrel->GetSocketLocation(FName("Projectile"));
		FRotator StartRotation = this->m_barrel->GetSocketRotation(FName("Projectile"));
		AProjectile* NewProjectile = this->GetWorld()->SpawnActor<AProjectile>(this->m_projectileBlueprint, StartLocation, StartRotation);
		NewProjectile->LaunchProjectile(this->m_launchSpeed);

		m_lastFireTime = FPlatformTime::Seconds();
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(m_barrel))
		return;

	//work out difference between current barrel rotation and aimdirection
	FRotator BarrelRotator = this->m_barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator : %s"), *AimAsRotator.ToString());

	FRotator DeltaRotator = AimAsRotator - BarrelRotator;	

	this->m_barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	if (!ensure(m_turret))
		return;

	//work out difference between current turret rotation and aimdirection
	FRotator TurretRotator = this->m_turret->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator : %s"), *AimAsRotator.ToString());

	FRotator DeltaRotator = AimAsRotator - TurretRotator;

	this->m_turret->Rotate(DeltaRotator.Yaw);
}

