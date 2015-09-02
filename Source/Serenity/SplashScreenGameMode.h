// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "SplashScreenGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SERENITY_API ASplashScreenGameMode : public AGameMode
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void LoadLevel();

	FTimerHandle time_handler;
	
	
};
