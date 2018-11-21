// Fill out your copyright notice in the Description page of Project Settings.

#include "Gm_ActionBase.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "CharacterBase.h"


AGm_ActionBase::AGm_ActionBase()
{
	TimeBetweenWave = 2.0f;
}



void AGm_ActionBase::StartWave()
{
	WaveCount++;

	NumOfBotsToSpawn = 2 * WaveCount;

	GetWorldTimerManager().SetTimer(TimerHandle_BotSpawner, this, &AGm_ActionBase::SpawnBotTimerElapsed, 1.0f, true, 1.0f);
}


void AGm_ActionBase::SpawnBotTimerElapsed()
{
	SpawnNewBot();

	NumOfBotsToSpawn--;
	if (NumOfBotsToSpawn <= 0)
	{
		EndWave();
		CheckWaveSate();
	}
}

void AGm_ActionBase::EndWave()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_BotSpawner);



}

void AGm_ActionBase::PrepareForNextWave()
{

	
	GetWorldTimerManager().SetTimer(TimerHandle_NextWaveStart, this, &AGm_ActionBase::StartWave, TimeBetweenWave, false);
}


void AGm_ActionBase::CheckWaveSate()
{
	bool bIsPreparingForWave = GetWorldTimerManager().IsTimerActive(TimerHandle_NextWaveStart);

	if (NumOfBotsToSpawn > 0 || bIsPreparingForWave)
	{
		return;
	}

	bool bIsAnybotAlive = false;
	for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
	{
		APawn* TestPawn = It->Get();
		if (TestPawn == nullptr || TestPawn->IsPlayerControlled())
		{
			continue;
		}
	}

	if (!bIsAnybotAlive)
	{
		PrepareForNextWave();
	}
}

void AGm_ActionBase::StartPlay()
{
	Super::StartPlay();

	PrepareForNextWave();
}
