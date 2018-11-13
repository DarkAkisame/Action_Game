// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "GA_TargetActorSelectGround.generated.h"


class UDecalComponent;
class USceneComponent;
/**
 * 
 */
UCLASS()
class ACTIONGAME_API AGA_TargetActorSelectGround : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()
	
public:
	AGA_TargetActorSelectGround();

	virtual void StartTargeting(UGameplayAbility* Ability) override;
	virtual void ConfirmTargetingAndContinue() override;
	virtual void Tick(float DeltaSeconds) override;
	UFUNCTION(BlueprintCallable, Category = "SelectGround")
		bool GetPlayerLookingPoint(FVector& OutViewPoint);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn= true), Category = "SelectGround")
		float Radius;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SelectGround")
		UDecalComponent* Decal;

	USceneComponent* RootComp;
};
