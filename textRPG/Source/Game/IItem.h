#pragma once
#include <string>

#include "Character.h"



class IItem
{
public:
	virtual ~IItem() = default;

	virtual std::string GetName() const = 0;

	virtual void Use(Character* character) = 0;

	virtual bool IsConsumable() const = 0;

};
