// Fill out your copyright notice in the Description page of Project Settings.
#include "Public/SpaceShip.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "EnhancedInputComponent.h"
#include "Public/Projectile.h"


// Sets default values
ASpaceShip::ASpaceShip()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCharacterMovement()->MaxWalkSpeed = 150.f;
}

// Called when the game starts or when spawned
void ASpaceShip::BeginPlay()
{
	Super::BeginPlay();

	check(GEngine != nullptr);

	// Get the player controller for this character
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		// Get the enhanced input local player subsystem and add a new input mapping context to it
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}	
}

// Called every frame
void ASpaceShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASpaceShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASpaceShip::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASpaceShip::Look);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &ASpaceShip::Fire);
	}
}

void ASpaceShip::Move (const FInputActionValue& Value)
{
	FVector2D MovementValue = Value.Get<FVector2D>();

	if (Controller)
	{
		const FVector Right = FVector::RightVector;
		const FVector Forward = FVector::ForwardVector;
		AddMovementInput(Right, MovementValue.X);
		AddMovementInput(Forward, MovementValue.Y);
	}
}

void ASpaceShip::Look (const FInputActionValue& Value)
{
	FVector2D LookAxisValue = Value.Get<FVector2D>();

	if (Controller)
	{
		AddControllerYawInput(LookAxisValue.X);
	}
}

void ASpaceShip::Fire()
{
	// Attempt to fire a projectile.
	if (Projectile)
	{
		// Get the camera transform.
		FVector Location = GetActorLocation();
		FRotator Rotation = FRotator(0.0f ,GetActorRotation().Yaw ,0.0f );
		
		FVector MuzzleOffset = FVector(75.0f, 0.0f, 0.0f);
	         
		// Transform MuzzleOffset from camera space to world space.
		FVector MuzzleLocation = Location + FTransform(Rotation).TransformVector(MuzzleOffset);
		FRotator MuzzleRotation = Rotation;
	 
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();
	 
			// Spawn the projectile at the muzzle.
			AProjectile* ProjectileToShoot = World->SpawnActor<AProjectile>(Projectile, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (ProjectileToShoot)
			{
				// Set the projectile's initial trajectory.
				FVector LaunchDirection = MuzzleRotation.Vector();
				ProjectileToShoot->FireInDirection(LaunchDirection);
			}
		}
	}
}

void ASpaceShip::Hit()
{
	HealthPoint --;

}

void ASpaceShip::AddScore()
{
	Score = Score + 10;
}

