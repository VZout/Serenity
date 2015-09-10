// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "GameFramework/GameMode.h"
#include "SerenityGameMode.generated.h"
/**
 * 
 */
UCLASS()
class SERENITY_API ASerenityGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	/** Called when the game starts. */
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Data")
	public int money = 10;

	/** Remove the current menu widget and create a new one from the specified class, if provided. */
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

	/** The widget class we will use as our menu when the game starts. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	TSubclassOf<UUserWidget> StartingWidgetClass;

	//Quest MyQuest;
	


protected:
	
	/** The widget instance that we are using as our menu. */
	UPROPERTY()
	UUserWidget* CurrentWidget;
	
};
