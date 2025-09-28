// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Launcher.generated.h"

UCLASS()
class SPACESHOOTER4_API ALauncher : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	ALauncher();
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AAsteroides> Asteroid;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void Launch();
};


