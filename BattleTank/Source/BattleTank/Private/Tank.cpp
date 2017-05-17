// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;	
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

/*
void ATank::AimAt(FVector HitLocation)
{
	if (!ensure(this->m_tankAimingComponent != nullptr))
		return;
	//UE_LOG(LogTemp, Warning, TEXT("TANK %s aiming at %s"), *this->GetName(), *(HitLocation.ToString()));

	this->m_tankAimingComponent->AimAt(HitLocation, m_launchSpeed);
}
*/

void ATank::Fire()
{
	if (!ensure(this->m_barrel))
		return;

	bool bIsReloaded = (FPlatformTime::Seconds() - m_lastFireTime) >= m_reloadTimeInSeconds ? true : false;

	if (bIsReloaded)
	{
		//UE_LOG(LogTemp, Warning, TEXT("%f TANK Fire"), this->GetWorld()->GetTimeSeconds());

		FVector StartLocation = this->m_barrel->GetSocketLocation(FName("Projectile"));
		FRotator StartRotation = this->m_barrel->GetSocketRotation(FName("Projectile"));
		AProjectile* NewProjectile = this->GetWorld()->SpawnActor<AProjectile>(this->m_projectileBlueprint, StartLocation, StartRotation);
		NewProjectile->LaunchProjectile(this->m_launchSpeed);

		m_lastFireTime = FPlatformTime::Seconds();
	}
}


