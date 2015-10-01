// Fill out your copyright notice in the Description page of Project Settings.

#include "Serenity.h"
#include "SplashScreenGameMode.h"

void ASplashScreenGameMode::BeginPlay() {
	Super::BeginPlay();

	PrimaryActorTick.bCanEverTick = true;

	//GetWorldTimerManager().SetTimer(this, &ASplashScreenGameMode::LoadLevel, 9.2f, false);
	FTimerHandle th;
	GetWorldTimerManager().SetTimer(th, this, &ASplashScreenGameMode::LoadLevel, 9.2f);

}

void ASplashScreenGameMode::Tick(float DeltaTime) {
		Super::Tick(DeltaTime);
}

void ASplashScreenGameMode::LoadLevel() {
	FLatentActionInfo info;
	UE_LOG(LogTemp, Warning, TEXT("Should load game level"));
	UGameplayStatics::OpenLevel(this, TEXT("MainMenu"));
	//GetWorldTimerManager().ClearTimer(this, &ASplashScreenGameMode::LoadLevel);
}


