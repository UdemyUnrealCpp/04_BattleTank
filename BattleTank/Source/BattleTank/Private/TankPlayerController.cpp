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



ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(this->GetPawn());
}

