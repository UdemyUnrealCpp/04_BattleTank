// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"
#include "Tank.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UTankAimingComponent* AimComp = this->GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(AimComp)) { return; }
		
	FoundAimingComponent(AimComp);
}


void ATankPlayerController::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);
    AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; } //if not possessing

	UTankAimingComponent* AimComp = this->GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimComp)) { return; }

	FVector hitLocation = FVector::ZeroVector;
	bool bGotHitLocation = GetSightRayHitLocation(hitLocation);
	if (bGotHitLocation)
	{		
		//tell controlled tank to aim at this point
		AimComp->AimAt(hitLocation);
	}
}

//Get world location if linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const
{
	//find crosshair position in pixel coordinate
	int32 iViewportSizeX, iViewportSizeY;
	GetViewportSize(iViewportSizeX, iViewportSizeY);
	FVector2D ScreenLocation = FVector2D(iViewportSizeX * this->CrosshairXLocation, iViewportSizeY * this->CrosshairYLocation);
	//UE_LOG(LogTemp, Warning, TEXT("Screen location : %s"), *ScreenLocation.ToString());

	//deproject the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Look Direction : %s"), *LookDirection.ToString());
		
		//line trace along that look direction and see what we hit (up to max range)
		return GetLookVectorHitLocation(LookDirection, HitLocation);		
	}
	return false;
}

//deproject the screen position of the crosshair to a world direction
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{	
	FVector WorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, LookDirection);	
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	//get camera location
	FVector StartLocation = this->PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + (LookDirection * LineTraceRangeCentimeters);
	FCollisionQueryParams TraceParams = FCollisionQueryParams(FName(TEXT("")), false, this->GetPawn());

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Camera, TraceParams))
	{
		HitLocation = HitResult.Location;
		//UE_LOG(LogTemp, Warning, TEXT("HIT : %s"), *HitResult.GetActor()->GetName());
		//UE_LOG(LogTemp, Warning, TEXT("HIT Location : %s"), *HitLocation.ToString());
		return true;
	}

	HitLocation = FVector(0);
	return false;
}

void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		ATank* PossessedTank = Cast<ATank>(InPawn);

		if (!ensure(PossessedTank)) { return; }

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
	}
}

void ATankPlayerController::OnPossessedTankDeath()
{
	StartSpectatingOnly();
}


