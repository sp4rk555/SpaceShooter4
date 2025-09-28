// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Projectile.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Public/Asteroides.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Create BoxComponent and set as RootComponent for the Actor
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	RootComponent = BoxCollision;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(BoxCollision);
	ProjectileMovementComponent->InitialSpeed = 800.0f;
	ProjectileMovementComponent->MaxSpeed = 800.0f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	InitialLifeSpan = 2.5f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	this->OnActorBeginOverlap.AddDynamic(this, &AProjectile::OnOverlapBegin);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::FireInDirection(const FVector& Direction)
{
	ProjectileMovementComponent->Velocity = Direction * ProjectileMovementComponent->InitialSpeed;
}

void AProjectile::OnOverlapBegin(AActor* MyActor, AActor* OtherActor)
{

	if (OtherActor && OtherActor != this)
	{
		AAsteroides* Asteroide = Cast<AAsteroides>(OtherActor);

		if (Asteroide)
		{
			Asteroide->Hit();
			Destroy();
		}
	}
}

