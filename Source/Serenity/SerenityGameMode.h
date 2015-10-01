// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PanelWidget.h"
#include "VerticalBox.h"
#include "VerticalBoxSlot.h"
#include "TextBlock.h"
#include "Quest.h"
#include "FlyByRing.h"
#include "Cargo.h"
#include "PlayerShip.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/GameMode.h"
#include "SerenityGameMode.generated.h"
/**
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
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void UpdateUI();
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void AddMoney(int32 amount);
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void RemoveAvailableQuest(int32 index);
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void RemoveActiveQuest(int32 index);
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	FQuest& GetAvailableQuest(int32 index);
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	FQuest& GetActiveQuest(int32 index);
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	FQuest& GetActiveQuestByType(int32 type);
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	bool HasActiveQuestByType(int32 type);
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void AddAvailableQuest(FString name, FString description, int32 reward, int32 type, int32 neededProgress);
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void AddCargo(int32 type);
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void RemoveCargo(int32 type, int32 amount);
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	bool HasCargo(int32 type, int32 amount);
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void AcceptQuest(int32 id);
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void AddProgressToQuest(int32 progress, int32 id);
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void CompleteQuest(int32 id);
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void AbandonQuest(int32 id);
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	int32 GetMoney();
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void SpawnFlyTroughRings(int32 amount, const FVector& Loc, const FRotator& Rot);
	void DestroyPopup();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	TSubclassOf<UUserWidget> StartingWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	TSubclassOf<UUserWidget> ButtonWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	TSubclassOf<UUserWidget> JournalButtonWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI Popup")
	TSubclassOf<UUserWidget> PopupCompleteWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI Popup")
	TSubclassOf<UUserWidget> PopupAcceptWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI Popup")
	UClass* FlyByRingPrefab;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	UTextBlock* QuestDescription;

	TArray<FQuest> AvailableQuests;
	TArray<FQuest> ActiveQuests;
	TArray<FTimerHandle> PopupTimers;
	TArray<UUserWidget*> PopupWidgets;
	TArray<FCargo> CargoList;

protected:
	
	UPROPERTY()
	UUserWidget* CurrentWidget;

	int32 questsIDs;
	
};

