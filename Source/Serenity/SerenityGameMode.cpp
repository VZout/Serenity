// Fill out your copyright notice in the Description page of Project Settings.

#include "Serenity.h"
#include "SerenityGameMode.h"

void ASerenityGameMode::BeginPlay() {
	Super::BeginPlay();
	money = 10;

	QuestDescription = NULL;
	questsIDs = 0;

	AddAvailableQuest("Problems in space.", "The space station needs your help! Go to the space station to view all available quests.", 75, 99, 0);
	AcceptQuest(0);
	AddAvailableQuest("Collect some stuff!", "I lost some of my goods when i got attacked by space pirates. Could you please get them back for me?.", 150, 98, 5);
	AddAvailableQuest("Flying Hoops", "I want you to prove to me that you are a good pilot. Fly trough 5 hoops that are floating arround.", 300, 97, 5);
	AddAvailableQuest("Collecting Minerals", "Please delive us some bauxite. We will pay you.", 200, 96, 2);

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
		if (CurrentWidget != nullptr) {
			UpdateUI();
			CurrentWidget->AddToViewport();
		}
	}
}

void ASerenityGameMode::UpdateUI() {
	UTextBlock* moneyText = (UTextBlock*)CurrentWidget->GetWidgetFromName(FName(TEXT("MoneyText")));
	UVerticalBox* ssQuestPanel = (UVerticalBox*)CurrentWidget->GetWidgetFromName(FName(TEXT("QuestOptainPanel")));
	UVerticalBox* invQuestPanel = (UVerticalBox*)CurrentWidget->GetWidgetFromName(FName(TEXT("ActiveQuestsPanel")));
	QuestDescription = (UTextBlock*)CurrentWidget->GetWidgetFromName(FName(TEXT("QuestDescBox")));
	
	if(moneyText) {
		FString moneyString =  "$" + FString::FromInt(money);
		moneyText->SetText(FText::FromString(moneyString));
	}
	if (ssQuestPanel) {
		ssQuestPanel->ClearChildren();
		for (int32 i = 0; i < AvailableQuests.Num(); i++) {
			UUserWidget* newButton = CreateWidget<UUserWidget>(GetWorld(), ButtonWidget);
			UTextBlock* buttonText = (UTextBlock*)newButton->GetWidgetFromName(FName(TEXT("QuestName")));
			buttonText->SetText(FText::FromString(AvailableQuests[i].name));
			UTextBlock* buttonDesc = (UTextBlock*)newButton->GetWidgetFromName(FName(TEXT("QuestDesc")));
			buttonDesc->SetText(FText::FromString(AvailableQuests[i].desc));
			UTextBlock* buttonID = (UTextBlock*)newButton->GetWidgetFromName(FName(TEXT("QuestID")));
			buttonID->SetText(FText::FromString(FString::FromInt(AvailableQuests[i].id)));
			UVerticalBoxSlot* slot = ssQuestPanel->AddChildToVerticalBox(newButton);
			FSlateChildSize size; 
			slot->SetSize(size); // Unreal engine fuckup
		}
	}

	if (invQuestPanel) {
		for (int32 i = 0; i < ActiveQuests.Num(); i++) {
			UUserWidget* newButton = CreateWidget<UUserWidget>(GetWorld(), JournalButtonWidget);
			UTextBlock* buttonText = (UTextBlock*)newButton->GetWidgetFromName(FName(TEXT("QuestName")));
			buttonText->SetText(FText::FromString(ActiveQuests[i].name));
			UTextBlock* buttonDesc = (UTextBlock*)newButton->GetWidgetFromName(FName(TEXT("QuestDesc")));
			buttonDesc->SetText(FText::FromString(ActiveQuests[i].desc));
			UTextBlock* buttonID = (UTextBlock*)newButton->GetWidgetFromName(FName(TEXT("QuestID")));
			buttonID->SetText(FText::FromString(FString::FromInt(ActiveQuests[i].id)));
			UVerticalBoxSlot* slot = invQuestPanel->AddChildToVerticalBox(newButton);
			FSlateChildSize size;
			slot->SetSize(size); // Unreal engine fuckup
		}
	}
}

void ASerenityGameMode::AddMoney(int32 amount) {
	money += amount;
	UpdateUI();
}

void ASerenityGameMode::AddCargo(int32 type) {
	CargoList.Add(FCargo(type));
}

void ASerenityGameMode::RemoveCargo(int32 type, int32 amount) {
	int32 deleteCount = 0;
	for (int32 i = 0; i < CargoList.Num(); i++) {
		if (CargoList[i].type == type && deleteCount < amount) {
			deleteCount++;
		}
	}
}

bool ASerenityGameMode::HasCargo(int32 type, int32 amount) {
	int32 hasCount = 0;
	for (int32 i = 0; i < CargoList.Num(); i++) {
		if (CargoList[i].type == type) {
			hasCount++;
		}
	}

	if (hasCount >= amount)
		return true;
	else
		return false;
}

int32 ASerenityGameMode::GetMoney() {
	return money;
}

void ASerenityGameMode::RemoveAvailableQuest(int32 index) {
	for (int32 i = 0; i < AvailableQuests.Num(); i++) {
		if (index == AvailableQuests[i].id) {
			AvailableQuests.RemoveAt(i);
		}
	}
}

void ASerenityGameMode::RemoveActiveQuest(int32 index) {
	for (int32 i = 0; i < ActiveQuests.Num(); i++) {
		if (index == ActiveQuests[i].id) {
			ActiveQuests.RemoveAt(i);
		}
	}
}

FQuest& ASerenityGameMode::GetAvailableQuest(int32 index) {
	for (int32 i = 0; i < AvailableQuests.Num(); i++) {
		if (index == AvailableQuests[i].id) {
			return AvailableQuests[i];
		}
	}
	return  AvailableQuests[0];
}

FQuest& ASerenityGameMode::GetActiveQuest(int32 index) {
	for (int32 i = 0; i < ActiveQuests.Num(); i++) {
		if (index == ActiveQuests[i].id) {
			return ActiveQuests[i];
		}
	}
	return  ActiveQuests[0];
}

FQuest& ASerenityGameMode::GetActiveQuestByType(int32 type) {
	for (int32 i = 0; i < ActiveQuests.Num(); i++) {
		if (type == ActiveQuests[i].type) {
			return ActiveQuests[i];
		}
	}
	return ActiveQuests[0];
}

bool ASerenityGameMode::HasActiveQuestByType(int32 type) {
	for (int32 i = 0; i < ActiveQuests.Num(); i++) {
		if (type == ActiveQuests[i].type) {
			return true;
		}
	}
	return false;
}

void  ASerenityGameMode::CompleteQuest(int32 id) {
	AddMoney(GetActiveQuest(id).reward);
	UUserWidget* popup = CreateWidget<UUserWidget>(GetWorld(), PopupCompleteWidgetClass);
	popup->AddToViewport();
	RemoveActiveQuest(id);
	PopupWidgets.Add(popup);
	FTimerHandle th;
	PopupTimers.Add(th);
	GetWorldTimerManager().SetTimer(th, this, &ASerenityGameMode::DestroyPopup, 2.5f);
}

void ASerenityGameMode::AddAvailableQuest(FString name, FString description, int32 reward, int32 type, int32 neededProgress) {
	AvailableQuests.Add(FQuest(questsIDs, name, description, reward, type, neededProgress));
	questsIDs++;
}

void ASerenityGameMode::AddProgressToQuest(int32 progress, int32 id) {
	GetActiveQuest(id).progress += progress;

	if (GetActiveQuest(id).progress >= GetActiveQuest(id).neededProgress) {
		CompleteQuest(id);
	}
}

void ASerenityGameMode::AcceptQuest(int32 index) {
	if (GetAvailableQuest(index).type == 97) {
		SpawnFlyTroughRings(GetAvailableQuest(index).neededProgress, FVector(0, 0, 0), FRotator(90, 0, 90));
	}

	ActiveQuests.Add(GetAvailableQuest(index));
	RemoveAvailableQuest(index);
	UUserWidget* popup = CreateWidget<UUserWidget>(GetWorld(), PopupAcceptWidgetClass);
	popup->AddToViewport();
	PopupWidgets.Add(popup);
	FTimerHandle th;
	PopupTimers.Add(th);
	GetWorldTimerManager().SetTimer(th, this, &ASerenityGameMode::DestroyPopup, 2.5f);

}

void ASerenityGameMode::AbandonQuest(int32 index) {
	RemoveActiveQuest(index);
}

void ASerenityGameMode::DestroyPopup() {
	PopupWidgets[0]->RemoveFromViewport();
	GetWorldTimerManager().ClearTimer(PopupTimers[0]);
}

void ASerenityGameMode::SpawnFlyTroughRings(int32 amount, const FVector& Loc, const FRotator& Rot) {
	float minDistance = 0;
	float maxDistance = 0;
	float positionmargin = 0;
	float rotationMargin = 0;
	AFlyByRing* fr = APlayerShip::SpawnBP<AFlyByRing>(GetWorld(), FlyByRingPrefab, Loc, Rot);
	fr->SetTarget();
	fr->SetActive(true);
	//fr->ResetChilds();
	fr->OnSpawned();

	for (int32 i = 1; i < amount; i++) {
		AFlyByRing* or = APlayerShip::SpawnBP<AFlyByRing>(GetWorld(), FlyByRingPrefab, Loc + FVector(500 * i,0,0), Rot);
		or->id = i;
		if (i == amount - 1) {
			or->isFinal = true;
		}
	}
}