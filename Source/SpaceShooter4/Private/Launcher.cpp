// Fill out your copyright notice in the Description page of Project Settings.



#include "Public/Launcher.h"

#include "Public/Asteroides.h"

// Sets default values
ALauncher::ALauncher()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ALauncher::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALauncher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	int WillSpawn =  FMath::RandRange(1,150);
	if (WillSpawn == 1)
	{
		Launch();
	}
}

void ALauncher::Launch()
{
	// Attempt to fire a projectile.
	if (Asteroid)
	{
		// Get the camera transform.-500 800
		FVector Location = FVector::ZeroVector;
		int SideSpawn = FMath::RandRange(1,4);
		if (SideSpawn == 1)
		{
			Location = FVector(-500.0f,FMath::RandRange(-800.0f,800.0f),90.0f);
		}
		if (SideSpawn == 2)
		{
			Location = FVector(500.0f,FMath::RandRange(-800.0f,800.0f),90.0f);
		}
		if (SideSpawn == 3)
		{
			Location = FVector(FMath::RandRange(-500.0f,500.0f),800.0f,90.0f);
		}
		if (SideSpawn == 4)
		{
			Location = FVector(FMath::RandRange(-500.0f,500.0f),-800.0f,90.0f);
		}
		
		FRotator Rotation = FRotator::ZeroRotator;
		if (SideSpawn == 1)
		{
			if (Location.Y <= 0.0f)
			{
				Rotation = FRotator(0.0f , FMath::RandRange(0.0f,60.0f),0.0f );
			}
			else
			{
				Rotation = FRotator(0.0f , FMath::RandRange(-60.0f,0.0f),0.0f );
			}
		}
		if (SideSpawn == 2)
		{
			if (Location.Y <= 0.0f)
			{
				Rotation = FRotator(0.0f , FMath::RandRange(120.0f,180.0f),0.0f );
			}
			else
			{
				Rotation = FRotator(0.0f , FMath::RandRange(180.0f,240.0f),0.0f );
			}
		}
		if (SideSpawn == 3)
		{
			if (Location.X <= 0.0f)
			{
				Rotation = FRotator(0.0f , FMath::RandRange(-30.0f,-90.0f),0.0f );
			}
			else
			{
				Rotation = FRotator(0.0f , FMath::RandRange(-90.0f,-150.0f),0.0f );
			}
		}
		if (SideSpawn == 4)
		{
			if (Location.X <= 0.0f)
			{
				Rotation = FRotator(0.0f , FMath::RandRange(30.0f,90.0f),0.0f );
			}
			else
			{
				Rotation = FRotator(0.0f , FMath::RandRange(90.0f,150.0f),0.0f );
			}
		}
	         
		// Transform MuzzleOffset from camera space to world space.
		FVector MuzzleLocation = Location;
		FRotator MuzzleRotation = Rotation;
	 
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();
	 
			// Spawn the projectile at the muzzle.
			AAsteroides* AsteroidesToLaunch = World->SpawnActor<AAsteroides>(Asteroid, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (AsteroidesToLaunch)
			{
				// Set the projectile's initial trajectory.
				FVector LaunchDirection = MuzzleRotation.Vector();
				AsteroidesToLaunch->GoInDirection(LaunchDirection);
			}
		}
	}
}

