// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force, and to apply forces to the tank
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public :

	//Sets a throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float fThrottle);
	
	//max force per track, in Nsewtons;
	UPROPERTY(EditDefaultsOnly, Category = "TankTrack")
	float TrackMaxDrivingForce = 400000.0f; //Assume 40 tonne tank, and 1g acceleration (40000 * 10)
};
