// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STS_Weapon.generated.h"

class UParticleSystem;

UCLASS()
class ARK_STEALTHSHOOTER_API ASTS_Weapon : public AActor
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent * WeaponMesh;

	UPROPERTY(EditDefaultsOnly, Category= "Settings")
	float ShotDistance;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	float ShotDamage;

	UPROPERTY(EditDefaultsOnly, Category = "Settings", meta = (ClampMin = 0.1f))
	float RoundsPerMinute;

	float TimeBetweenShots;
	float LastFireTime;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	bool bDrawDebug;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	UParticleSystem* ImpactEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	UParticleSystem* TracerEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	UParticleSystem* MuzzleEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	FName MuzzleSocketName;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	FName TracerTargetName;

	FTimerHandle TimerHandle_AutoFire;

public:	
	// Sets default values for this actor's properties
	ASTS_Weapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	void StartFire();
	void StopFire();

protected:
	void Fire();

};
