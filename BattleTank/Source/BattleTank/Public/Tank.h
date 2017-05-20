// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

	// Sets default values for this pawn's properties
	ATank();


private:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Health")
		int32 m_startingHealth = 100;


	UPROPERTY(VisibleAnywhere, Category="Health")
	int32 m_currentHealth = m_startingHealth;
};

