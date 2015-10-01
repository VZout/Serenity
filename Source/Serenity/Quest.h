// Copyright Viktor Zoutman

#pragma once

#include "Object.h"
#include "Quest.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct SERENITY_API FQuest
{
	GENERATED_USTRUCT_BODY()

	FQuest();
	FQuest(int32 id, FString name, FString description, int32 reward, int32 type, int32 neededProgress);
	~FQuest();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMG Game")
	int32 id;
	UPROPERTY(EditAnywhere, Category = "UMG Game")
	FString name;
	UPROPERTY(EditAnywhere, Category = "UMG Game")
	FString desc;
	UPROPERTY(EditAnywhere, Category = "UMG Game")
	int32 reward;
	UPROPERTY(EditAnywhere, Category = "UMG Game")
	int32 type;
	UPROPERTY(EditAnywhere, Category = "UMG Game")
	int32 neededProgress;
	UPROPERTY(EditAnywhere, Category = "UMG Game")
	int32 progress;
	
};
