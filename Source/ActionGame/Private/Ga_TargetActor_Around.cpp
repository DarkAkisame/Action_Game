// Fill out your copyright notice in the Description page of Project Settings.

#include "Ga_TargetActor_Around.h"
#include "GameFramework/PlayerController.h"
#include "GameplayAbility.h"
#include "GameFramework/Pawn.h"




void AGa_TargetActor_Around::StartTargeting(UGameplayAbility* Ability)
{
	OwningAbility = Ability;
	MasterPC = Cast<APlayerController>(Ability->GetOwningActorFromActorInfo()->GetInstigatorController());
}

void AGa_TargetActor_Around::ConfirmTargetingAndContinue()
{
	APawn* OnwingPawn = MasterPC->GetPawn();
	if (!OnwingPawn)
	{
		TargetDataReadyDelegate.Broadcast(FGameplayAbilityTargetDataHandle());
		return;
	}
	FVector ViewLocation = OnwingPawn->GetActorLocation();
	

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

	if (OverlapedActors.Num() > 0)
	{
		FGameplayAbilityTargetDataHandle TargetData = StartLocation.MakeTargetDataHandleFromActors(OverlapedActors);
		TargetDataReadyDelegate.Broadcast(TargetData);
	}
	else
	{
		TargetDataReadyDelegate.Broadcast(FGameplayAbilityTargetDataHandle());
	}
}
