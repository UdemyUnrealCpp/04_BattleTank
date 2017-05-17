// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	//Calculate the slippage speed
	//if tank goes to the right cause the physics he value will be high than one
	float SlippageSpeed = FVector::DotProduct(this->GetRightVector(), this->GetComponentVelocity());
	//Work out the required acceleration this frame to correct
	// a = v / t
	FVector CorrectionAcceleration = (-SlippageSpeed / DeltaTime) * this->GetRightVector();
	//Calculate and apply sideways for (F = m a)
	UStaticMeshComponent* TankRoot = Cast<UStaticMeshComponent>(this->GetOwner()->GetRootComponent());
	FVector CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2.0f; //divide by 2 cause 2 tracks
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float fThrottle)
{
	FVector ForceApplied = this->GetForwardVector() * fThrottle * this->TrackMaxDrivingForce;
	FVector ForceLocation = this->GetComponentLocation();
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(this->GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}


