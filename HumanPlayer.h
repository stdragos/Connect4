#pragma once
#include "IPlayer.h"
class HumanPlayer : public IPlayer
{
public:
	HumanPlayer(const std::string&);

	uint8_t GetNextAction() override;
};

