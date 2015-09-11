// Copyright Viktor Zoutman

#include "Serenity.h"
#include "Quest.h"

Quest::Quest() {
}

Quest::Quest(FString name, FString description, int32 reward, int32 type) {
	this->name = name;
	this->desc = description;
	this->reward = reward;
	this->type = type;
}

Quest::~Quest() {
}
