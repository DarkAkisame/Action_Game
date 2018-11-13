// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "Ga_TargetActor_Around.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAME_API AGa_TargetActor_Around : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()
	
public:

	void StartTargeting(UGameplayAbility* Ability) override;
	void ConfirmTargetingAndContinue()override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "FindAround")
		float Radius;
};
