// Fill out your copyright notice in the Description page of Project Settings.


#include "STS_BaseCharacter.h"
#include "GameFramework/PawnMovementComponent.h"
#include <STS_Weapon.h>
#include <STS_HealthComponent.h>

// Sets default values
ASTS_BaseCharacter::ASTS_BaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
	WeaponSocketName = "WPN_SCK";

	HealthComponent = CreateDefaultSubobject<USTS_HealthComponent>(TEXT("HEalthComponent"));
}

void ASTS_BaseCharacter::StartFire()
{
	if (IsValid(CurrentWeapon))
	{
		CurrentWeapon->StartFire();
	}
}

void ASTS_BaseCharacter::StopFire()
{
	if (IsValid(CurrentWeapon))
	{
		CurrentWeapon->StopFire();
	}
}

void ASTS_BaseCharacter::OnHealthChanged(USTS_HealthComponent* HealthComp, float Health, float HealthDelta, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
}

void ASTS_BaseCharacter::OnDeath(USTS_HealthComponent* HealthComp, AController* InstigatedBy, AActor* Killer)
{
	StopFire();
	GetMovementComponent()->StopMovementImmediately();
	this->SetActorEnableCollision(false);

}


// Called when the game starts or when spawned
void ASTS_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsValid(StartingWeaponClass))
	{
		CurrentWeapon = GetWorld()->SpawnActor<ASTS_Weapon>(StartingWeaponClass, FVector::ZeroVector, FRotator::ZeroRotator);
		if(IsValid(CurrentWeapon))
		{
			CurrentWeapon->SetOwner(this);
			CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocketName);
		}
	}


	if (IsValid(HealthComponent))
	{
		HealthComponent->OnHealthChanged.AddDynamic(this, &ASTS_BaseCharacter::OnHealthChanged);
		HealthComponent->OnDeath.AddDynamic(this, &ASTS_BaseCharacter::OnDeath);
	}

}

// Called every frame
void ASTS_BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



