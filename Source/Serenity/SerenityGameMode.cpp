// Fill out your copyright notice in the Description page of Project Settings.

#include "Serenity.h"
#include "SerenityGameMode.h"

void ASerenityGameMode::BeginPlay()
{
	Super::BeginPlay();
	ChangeMenuWidget(StartingWidgetClass);
}

//Could be used to hide menu. Should rewrite this tough TODO: make a proper user interface system
void ASerenityGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}





