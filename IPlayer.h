#pragma once
#include "Board.h"
#include <iostream>
class IPlayer
{
protected:
	std::string m_name;

public:
	IPlayer(const std::string&);
	virtual ~IPlayer() = default;

	const std::string& GetName() const;
	virtual uint8_t GetNextAction() = 0;
};

