// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STS_BaseCharacter.generated.h"


class ASTS_Weapon;
class USTS_HealthComponent;

UCLASS()
class ARK_STEALTHSHOOTER_API ASTS_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASTS_BaseCharacter();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASTS_Weapon>StartingWeaponClass;

	UPROPERTY(EditDefaultsOnly)
	FName WeaponSocketName;

	UPROPERTY(BlueprintReadOnly)
	ASTS_Weapon* CurrentWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USTS_HealthComponent* HealthComponent;

public:

	UFUNCTION(BlueprintCallable)
	void StartFire();

	UFUNCTION(BlueprintCallable)
	void StopFire();

	UFUNCTION(BlueprintCallable)
	void OnHealthChanged(USTS_HealthComponent* HealthComp, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION(BlueprintCallable)
	void OnDeath(USTS_HealthComponent* HealthComp, class AController* InstigatedBy, AActor* Killer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
