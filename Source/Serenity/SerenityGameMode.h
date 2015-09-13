// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Quest.h"
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
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data")
	int32 money;

	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);
	void UpdateUI();
	void AddMoney(int32 amount);
	int32 GetMoney();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	TSubclassOf<UUserWidget> StartingWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	TSubclassOf<UUserWidget> ButtonWidget;

	TArray<Quest> AvailableQuests;
	TArray<Quest> ActiveQuests;
	
protected:
	
	UPROPERTY()
	UUserWidget* CurrentWidget;
	
};
