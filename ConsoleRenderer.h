#pragma once
#include "Board.h"
#include "IPlayer.h"

class ConsoleRenderer
{
private:
public:
	ConsoleRenderer() = default;
	
	void Draw(const Board&, bool) const;
	void EndScreen(const IPlayer*, const Board&, bool) const;
	void EndScreen(const Board&, bool) const;
};

