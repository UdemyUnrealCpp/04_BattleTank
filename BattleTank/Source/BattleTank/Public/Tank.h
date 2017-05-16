// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//forward declaration
class UTankBarrel; 
class UTankTurret;
class UTankAimingComponent;
class AProjectile;
class UTankMovementComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* m_tankAimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* m_tankMovementComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float m_launchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float m_reloadTimeInSeconds = 3.0f;	

	UPROPERTY(EditAnywhere, Category = "Setup")
		TSubclassOf<AProjectile> m_projectileBlueprint;

	double m_lastFireTime = 0;

public:
	// Sets default values for this pawn's properties
	ATank();

	void AimAt(FVector HitLocation);
	UFUNCTION(BlueprintCallable, Category = "Fire")
		void Fire();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	
};
