// Fill out your copyright notice in the Description page of Project Settings.

#include "GA_TargetActorSelectGround.h"
#include "GameplayAbility.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "DrawDebugHelpers.h"
#include "Components/DecalComponent.h"
#include "Components/SceneComponent.h"




AGA_TargetActorSelectGround::AGA_TargetActorSelectGround()
{
	PrimaryActorTick.bCanEverTick = true;
	Decal = CreateDefaultSubobject <UDecalComponent>("Decal");
	RootComp = CreateDefaultSubobject<USceneComponent>("RootComp");
	SetRootComponent(RootComp);
	Decal->SetupAttachment(RootComp);
	Radius = 200.0f;
	Decal->DecalSize = FVector(Radius);
}

void AGA_TargetActorSelectGround::StartTargeting(UGameplayAbility* Ability)
{
	OwningAbility = Ability;
	MasterPC = Cast<APlayerController>(Ability->GetOwningActorFromActorInfo()->GetInstigatorController());
	Decal->DecalSize = FVector(Radius);
}

void AGA_TargetActorSelectGround::ConfirmTargetingAndContinue()
{
	FVector ViewLocation;
	GetPlayerLookingPoint(ViewLocation);

	TArray<FOverlapResult> Overlaps;
	TArray<TWeakObjectPtr<AActor>> OverlapedActors;
	bool TraceComplex = false;

	FCollisionQueryParams CollisionQueryPrams;
	CollisionQueryPrams.bTraceComplex = TraceComplex;
	CollisionQueryPrams.bReturnPhysicalMaterial = false;
	APawn* MasterPawn = MasterPC->GetPawn();
	if (MasterPawn)
	{
		CollisionQueryPrams.AddIgnoredActor(MasterPawn->GetUniqueID());
	}
	bool TryOverlap = GetWorld()->OverlapMultiByObjectType(Overlaps, ViewLocation, FQuat::Identity, FCollisionObjectQueryParams(ECC_Pawn), FCollisionShape::MakeSphere(Radius), CollisionQueryPrams);
	if (TryOverlap)
	{
		for (int32 i = 0; i < Overlaps.Num(); ++i)
		{
			APawn* PawnOverLaped = Cast<APawn>(Overlaps[i].GetActor());
			if (PawnOverLaped && !OverlapedActors.Contains(PawnOverLaped))
			{
				OverlapedActors.Add(PawnOverLaped);
			}
		}
	}

	FGameplayAbilityTargetData_LocationInfo* CenterLoction = new FGameplayAbilityTargetData_LocationInfo();
	if (Decal)
	{
		CenterLoction->TargetLocation.LiteralTransform = Decal->GetComponentTransform();
		CenterLoction->TargetLocation.LocationType = EGameplayAbilityTargetingLocationType::LiteralTransform;
	}
	

	if (OverlapedActors.Num() > 0)
	{
		FGameplayAbilityTargetDataHandle TargetData = StartLocation.MakeTargetDataHandleFromActors(OverlapedActors);
		TargetData.Add(CenterLoction);
		TargetDataReadyDelegate.Broadcast(TargetData);
	}
	else
	{
		TargetDataReadyDelegate.Broadcast(FGameplayAbilityTargetDataHandle(CenterLoction));
	}
}

void AGA_TargetActorSelectGround::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FVector LookPoint;
	GetPlayerLookingPoint(LookPoint);
	Decal->SetWorldLocation(LookPoint);
}

bool AGA_TargetActorSelectGround::GetPlayerLookingPoint(FVector& OutViewPoint)

{
	FVector ViewPoint;
	FRotator ViewRoatation;
	MasterPC->GetPlayerViewPoint(ViewPoint, ViewRoatation);
	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = true;
	APawn* MasterPawn = MasterPC->GetPawn();
	if (MasterPawn)
	{
		QueryParams.AddIgnoredActor(MasterPawn->GetUniqueID());
	}
	bool TryTrace = GetWorld()->LineTraceSingleByChannel(HitResult, ViewPoint, ViewPoint + ViewRoatation.Vector()*10000.0f, ECC_Visibility, QueryParams);
	if (TryTrace)
	{
		OutViewPoint = HitResult.ImpactPoint;

	}
	else
	{
		OutViewPoint = FVector();
	}
	return TryTrace;
}
