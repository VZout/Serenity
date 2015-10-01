// Copyright Viktor Zoutman

#include "Serenity.h"
#include "Quest.h"

FQuest::FQuest() {
}

FQuest::FQuest(int32 id, FString name, FString description, int32 reward, int32 type, int32 neededProgress) {
	this->name = name;
	this->desc = description;
	this->reward = reward;
	this->type = type;
	this->id = id;
	this->neededProgress = neededProgress;
	this->progress = 0;
}

FQuest::~FQuest() {
}