// Fill out your copyright notice in the Description page of Project Settings.


#include "STS_Weapon.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "ARK_StealthShooter/ARK_StealthShooter.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASTS_Weapon::ASTS_Weapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = WeaponMesh;
	ShotDistance = 10000.0f;
	ShotDamage = 20.0f;
	RoundsPerMinute = 600.0f;
	bDrawDebug = false;
	MuzzleSocketName = "MuzzleSocket";
	TracerTargetName = "BeamEnd";
}

// Called when the game starts or when spawned
void ASTS_Weapon::BeginPlay()
{
	Super::BeginPlay();
	TimeBetweenShots = 60 / RoundsPerMinute;
}

void ASTS_Weapon::StartFire()
{
	float FirstDelay = FMath::Max(0.0f, LastFireTime + TimeBetweenShots - GetWorld()->TimeSeconds);
	GetWorldTimerManager().SetTimer(TimerHandle_AutoFire, this, &ASTS_Weapon::Fire, TimeBetweenShots, true, FirstDelay);
}

void ASTS_Weapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_AutoFire);
}

void ASTS_Weapon::Fire()
{
	AActor* MyOwner = GetOwner();
	if (IsValid(MyOwner))
	{
		FVector EyeLocation;
		FRotator EyeRotation;
		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		FVector ShotDirection = EyeRotation.Vector();

		FVector TraceEnd = EyeLocation + (ShotDirection * ShotDistance);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(MyOwner);
		QueryParams.AddIgnoredActor(this);
		QueryParams.bTraceComplex = true;

		FVector ImpactPoint = TraceEnd;

		FHitResult Hit;

		if (GetWorld() -> LineTraceSingleByChannel(Hit,EyeLocation, TraceEnd, WEAPOM_COLLISION, QueryParams))
		{
			AActor* HitActor = Hit.GetActor();
			UGameplayStatics::ApplyPointDamage(HitActor, 
				ShotDamage,
				ShotDirection,
				Hit, 
				MyOwner->GetInstigatorController(), 
				MyOwner,
				DamageType);

			if (IsValid(ImpactEffect))
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
			}

			ImpactPoint = Hit.ImpactPoint;
			 
		}

		if (bDrawDebug)
		{
            DrawDebugLine(GetWorld(), EyeLocation, Hit.ImpactPoint, FColor::White, false, 1.0f,0,1.0f);
		}
        
		if (IsValid(MuzzleEffect))
		{
            UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, WeaponMesh,MuzzleSocketName);
		}

		if (IsValid(TracerEffect))
		{
			UParticleSystemComponent * TracerComponent = UGameplayStatics::SpawnEmitterAttached(TracerEffect, WeaponMesh, MuzzleSocketName);
		
			if (IsValid(TracerComponent))
			{
				TracerComponent->SetVectorParameter(TracerTargetName, ImpactPoint);
			}
		}

        LastFireTime = GetWorld()->TimeSeconds;
	}
}

