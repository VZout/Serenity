// Fill out your copyright notice in the Description page of Project Settings.

#include "Serenity.h"
#include "SerenityGameMode.h"

#include "TextBlock.h"

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
			CurrentWidget->AddToViewport();
		}
	}
	UpdateUI();
}

void ASerenityGameMode::UpdateUI() {
	UTextBlock* t = (UTextBlock*)CurrentWidget->GetWidgetFromName(FName(TEXT("MoneyText")));
	
	if(t) {
		FString moneyString =  "$" + FString::FromInt(money);

		t->SetText(FText::FromString(moneyString));
	}

}

void ASerenityGameMode::AddMoney(int32 amount) {
	money += amount;
	UpdateUI();
}

int32 ASerenityGameMode::GetMoney() {
	return money;
}





