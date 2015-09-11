// Copyright Viktor Zoutman

#pragma once

/**
 * 
 */
class SERENITY_API Quest
{
public:
	FString name;
	FString desc;
	int32 reward;
	int32 type;

	Quest();
	Quest(FString name, FString description, int32 reward, int32 type);
	~Quest();
};
