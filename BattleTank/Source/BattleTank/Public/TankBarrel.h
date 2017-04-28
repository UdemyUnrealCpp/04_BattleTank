// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	void Elevate(float DegreesPerSecond);
	
private:

	UPROPERTY(EditAnywhere, Category = Setup)
		float m_maxDegreesPerSecond = 20;
	UPROPERTY(EditAnywhere, Category = Setup)
		float m_elevationInDegreeMin = 0;
	UPROPERTY(EditAnywhere, Category = Setup)
		float m_elevationInDegreeMax = 40;
};
