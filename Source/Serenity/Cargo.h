// Copyright Viktor Zoutman

#pragma once

#include "Cargo.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct SERENITY_API FCargo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cargo")
	int32 type;

	FCargo();
	FCargo(int32 type);
	~FCargo();
};
