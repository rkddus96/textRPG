#pragma once
#include <string>

#include "Character.h"



class Item
{
public:
	virtual ~Item() = default;

	virtual std::string GetName() const = 0;

	virtual void Use(Character* character) = 0;

	virtual bool GetState() const = 0;

};

