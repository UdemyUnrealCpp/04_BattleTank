// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay tank play controller"));

	ATank* playerTank = this->GetControlledTank();

	if (playerTank == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("NO TANK"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TANK FOUND %s"), *(playerTank->GetName()));
	}	
}


void ATankPlayerController::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);
	AimTowardsCrosshair();
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(this->GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (GetControlledTank() == nullptr)
		return;

	FVector hitLocation = FVector::ZeroVector;

	if (GetSightRayHitLocation(hitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit location : %s"), *hitLocation.ToString());
		//tell controlled tank to aim at this point
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
		GetLookVectorHitLocation(LookDirection, HitLocation);		
	}
	return true;
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
	FCollisionQueryParams TraceParams = FCollisionQueryParams(FName(TEXT("")), false, GetControlledTank());

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility, TraceParams))
	{
		HitLocation = HitResult.Location;
		UE_LOG(LogTemp, Warning, TEXT("HIT : %s"), *HitResult.GetActor()->GetName());
		return true;
	}

	return false;
}


