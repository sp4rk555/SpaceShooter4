// Fill out your copyright notice in the Description page of Project Settings.



#include "Public/Asteroides.h"

#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Public/SpaceShip.h"

// Sets default values
AAsteroides::AAsteroides()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Create BoxComponent and set as RootComponent for the Actor.
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	RootComponent = BoxCollision;
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(BoxCollision);
	ProjectileMovementComponent->InitialSpeed = FMath::RandRange(100.0f,300.0f) ;
	ProjectileMovementComponent->MaxSpeed = ProjectileMovementComponent->InitialSpeed;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	InitialLifeSpan = 20.0f;
	
}

// Called when the game starts or when spawned
void AAsteroides::BeginPlay()
{
	Super::BeginPlay();
	this->OnActorBeginOverlap.AddDynamic(this, &AAsteroides::OnOverlapBegin);

}

// Called every frame
void AAsteroides::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAsteroides::GoInDirection(const FVector& Direction)
{
	ProjectileMovementComponent->Velocity = Direction * ProjectileMovementComponent->InitialSpeed;
}

void AAsteroides::OnOverlapBegin(AActor* MyActor, AActor* OtherActor)
{

	if (OtherActor && OtherActor != this)
	{
		ASpaceShip* SpaceShip = Cast<ASpaceShip>(OtherActor);

		if (SpaceShip)
		{
			SpaceShip->Hit();
			Destroy();
		}
	}
}

void AAsteroides::Hit()
{
	HealthPoint --;
	if (HealthPoint <= 0)
	{
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpaceShip::StaticClass(), FoundActors);
		if (FoundActors.Num() > 0)
		{
			AActor* Actor = FoundActors[0];
			ASpaceShip* SpaceShip = Cast<ASpaceShip>(Actor);
			SpaceShip->AddScore();
		}
		Destroy();
	}
}
