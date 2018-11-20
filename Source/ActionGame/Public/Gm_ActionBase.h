// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Gm_ActionBase.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAME_API AGm_ActionBase : public AGameModeBase
{
	GENERATED_BODY()

protected:


	FTimerHandle TimerHandle_BotSpawner;

	FTimerHandle TimerHandle_NextWaveStart;

	// Bots to spawn in current wave
	int32 NumOfBotsToSpawn;

	int32 WaveCount;

	UPROPERTY(EditDefaultsOnly, Category = "GameMode")
	float TimeBetweenWave;

	
protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
		void SpawnNewBot();
	
	void SpawnBotTimerElapsed();


	// start spawning AI
	void StartWave();

	// End spawning AI
	void EndWave();


	// Set timer for  next start wave
	void PrepareForNextWave();

	// checks wave state
	void CheckWaveSate();

public:

	AGm_ActionBase();

	virtual void StartPlay() override;
};
