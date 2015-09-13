// Fill out your copyright notice in the Description page of Project Settings.

#include "Serenity.h"
#include "SerenityGameMode.h"

#include "TextBlock.h"
#include "PanelWidget.h"
#include "GridPanel.h"
#include "GridSlot.h"

void ASerenityGameMode::BeginPlay() {
	Super::BeginPlay();
	money = 10;

	AvailableQuests.Add(Quest("Epic Quest", "The quest to save a princess", 50, 0));

	ChangeMenuWidget(StartingWidgetClass);
	UpdateUI();
}

//Could be used to hide menu. Should rewrite this tough TODO: make a proper user interface system
void ASerenityGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr) {
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr) {
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr)
		{
			UpdateUI();
			CurrentWidget->AddToViewport();
		}
	}
}

void ASerenityGameMode::UpdateUI() {
	UTextBlock* moneyText = (UTextBlock*)CurrentWidget->GetWidgetFromName(FName(TEXT("MoneyText")));
	UGridPanel* ssQuestPanel = (UGridPanel*)CurrentWidget->GetWidgetFromName(FName(TEXT("QuestOptainPanel")));
	
	if(moneyText) {
		FString moneyString =  "$" + FString::FromInt(money);
		moneyText->SetText(FText::FromString(moneyString));
	}
	if (ssQuestPanel) {
		
		for (int32 i = 0; i < 2; i++) {
			UUserWidget* newButton = CreateWidget<UUserWidget>(GetWorld(), ButtonWidget);
			UGridSlot* slot = ssQuestPanel->AddChildToGrid(newButton);
			slot->SetRow(i + 1);
			slot->SetColumn(1);
			ssQuestPanel->AddChildToGrid(newButton);
		}
	}

}

void ASerenityGameMode::AddMoney(int32 amount) {
	money += amount;
	UpdateUI();
}

int32 ASerenityGameMode::GetMoney() {
	return money;
}





