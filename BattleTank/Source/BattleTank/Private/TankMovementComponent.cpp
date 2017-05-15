// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"

#include "TankTrack.h"

#include "TankMovementComponent.h"


void UTankMovementComponent::Initialise(UTankTrack *LeftTrackToSet, UTankTrack *RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) { return; }

	this->LeftTrack = LeftTrackToSet;
	this->RightTrack = RightTrackToSet;	
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }

	UE_LOG(LogTemp, Warning, TEXT("Intend move forward : %f"), Throw);

	this->LeftTrack->SetThrottle(Throw);
	this->RightTrack->SetThrottle(Throw);

	//TODO prevent double speed due to dual control use
}


