// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"

#include "TankTrack.h"

#include "TankMovementComponent.h"


void UTankMovementComponent::Initialise(UTankTrack *LeftTrackToSet, UTankTrack *RightTrackToSet)
{
	this->LeftTrack = LeftTrackToSet;
	this->RightTrack = RightTrackToSet;	
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }

	//UE_LOG(LogTemp, Warning, TEXT("Intend move forward : %f"), Throw);

	this->LeftTrack->SetThrottle(Throw);
	this->RightTrack->SetThrottle(Throw);

	//TODO prevent double speed due to dual control use
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }

	//UE_LOG(LogTemp, Warning, TEXT("Intend turn right : %f"), Throw);

	this->LeftTrack->SetThrottle(Throw);
	this->RightTrack->SetThrottle(-Throw);

	//TODO prevent double speed due to dual control use
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	//FString TankName = this->GetOwner()->GetName();
	//FVector AIFowardIntention = MoveVelocity.GetSafeNormal();
	//UE_LOG(LogTemp, Warning, TEXT("%s moves velocity %s"), *TankName, *(AIFowardIntention.ToString()))

	FVector TankForward = this->GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector AIFowardIntention = MoveVelocity.GetSafeNormal();

	float Dot = FVector::DotProduct(TankForward, AIFowardIntention);
	IntendMoveForward(Dot);

	FVector Cross = FVector::CrossProduct(TankForward, AIFowardIntention);
	IntendTurnRight(Cross.Z);
}



