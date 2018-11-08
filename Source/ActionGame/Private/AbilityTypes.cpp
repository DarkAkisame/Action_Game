// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilityTypes.h"



FGameplayAbilityInfo::FGameplayAbilityInfo()
	:CooldownDurtation(0),
	Cost(0),
	CostType(EAbilityCostType ::Mana),
	UIMat(nullptr),
	AbilityClass(nullptr)
{

}

FGameplayAbilityInfo::FGameplayAbilityInfo(float InCooldownDurtation, float InCost, EAbilityCostType InCostType, UMaterialInstance* InUIMat, TSubclassOf<UGameplayAbilityBase> InAbilityClass)
	:CooldownDurtation(InCooldownDurtation),
	Cost(InCost),
	CostType(InCostType),
	UIMat(InUIMat),
	AbilityClass(InAbilityClass)
{

}
