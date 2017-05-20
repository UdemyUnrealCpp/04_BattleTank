// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	this->m_collisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	this->SetRootComponent(this->m_collisionMesh);
	this->m_collisionMesh->SetNotifyRigidBodyCollision(true);


	this->m_projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	this->m_projectileMovement->bAutoActivate = false;	

	this->m_launchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	this->m_launchBlast->AttachToComponent(this->RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	this->m_impactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	this->m_impactBlast->AttachToComponent(this->RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	this->m_impactBlast->bAutoActivate = false;

	this->m_explosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	this->m_explosionForce->AttachToComponent(this->RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();	

	this->m_collisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}


void AProjectile::LaunchProjectile(float Speed)
{
	this->m_projectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	this->m_projectileMovement->Activate();
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//UE_LOG(LogTemp, Warning, TEXT("HIT %s"), *HitComponent->GetName())

	this->m_launchBlast->Deactivate();
	this->m_impactBlast->Activate();

	this->m_explosionForce->FireImpulse();
}


