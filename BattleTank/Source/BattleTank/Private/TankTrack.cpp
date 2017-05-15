// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"



void UTankTrack::SetThrottle(float fThrottle)
{
	FString Name = this->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s Throttle : %f"), *Name, fThrottle);

	//TODO clamp actual  throttle value so player can't overdrive
	FVector ForceApplied = this->GetForwardVector() * fThrottle * this->TrackMaxDrivingForce;
	FVector ForceLocation = this->GetComponentLocation();
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(this->GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

	//UE_LOG(LogTemp, Warning, TEXT("Throttle : %f"), TankRoot->);
}


