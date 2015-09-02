// Copyright Viktor Zoutman

#pragma once

#include "Blueprint/UserWidget.h"
#include "GameFramework/GameMode.h"
#include "HyperSpaceGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SERENITY_API AHyperSpaceGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	/** Called when the game starts. */
	virtual void BeginPlay() override;

	/** Remove the current menu widget and create a new one from the specified class, if provided. */
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

protected:
	/** The widget class we will use as our menu when the game starts. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget> StartingWidgetClass;

	/** The widget instance that we are using as our menu. */
	UPROPERTY()
		UUserWidget* CurrentWidget;	
};
