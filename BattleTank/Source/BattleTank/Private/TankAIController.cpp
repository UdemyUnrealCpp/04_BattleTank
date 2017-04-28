// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "EngineUtils.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* aiTank = this->GetControlledTank();

	if(aiTank == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI HAS NOT TANK"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI CONTROL TANK %s"), *(aiTank->GetName()));
	}	

	this->Target = this->GetPlayerTank();

	if (Target == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("NO TANK PLAYER FOUND"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TANK PLAYER FOUND %s"), *(Target->GetName()));
	}
}

void ATankAIController::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	AimTowardsTarget();
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(this->GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	//loop through all APlayerController for the world
	for (TActorIterator<APlayerController> iterator(GetWorld()); iterator; ++iterator)
	{
		//search APlayerController (which is a parent of ATankPlayerController)
		ATank *playerTank = Cast<ATank>(iterator->GetPawn());

		if (playerTank)
		{
			//UE_LOG(LogTemp, Warning, TEXT("FOUND PLAYER CONTROLLER %s"), *(playerTank->GetName()));
			//return first player tank found
			return playerTank;
		}
	}

	return nullptr;
}

void ATankAIController::AimTowardsTarget()
{
	if (this->GetControlledTank() == nullptr)
		return;

	if (Target == nullptr)
		return;

	//this->GetControlledTank()->AimAt(Target->GetActorLocation());
}

