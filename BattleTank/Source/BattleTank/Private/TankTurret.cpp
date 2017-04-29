// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"


void UTankTurret::Rotate(float RelativeSpeed)
{
	//UE_LOG(LogTemp, Warning, TEXT("Turret Rotate Called at speed : %f"), RelativeSpeed);

	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f);
	float RotateSpeed = RelativeSpeed * this->m_maxDegreesPerSecond * this->GetWorld()->DeltaTimeSeconds;
	float RawNewRotation = this->RelativeRotation.Yaw + RotateSpeed;
	this->SetRelativeRotation(FRotator(0, RawNewRotation, 0));
}

