#pragma once
#include "IPlayer.h"
#include <vector>
#include <unordered_map>
#include <random>
#include <fstream>

class AIPlayer : public IPlayer
{
public:
	AIPlayer(Board&, const std::string&, const std::string&);
	~AIPlayer() override;

	// Inherited via IPlayer
	uint8_t GetNextAction() override;

	void FeedReward(float);

private:
	std::vector<uint8_t> GenerateActionCollection(const Board&);
	void SavePolicy() const;
	void LoadPolicy();

private:
	Board& m_board;
	std::unordered_map<std::string, float> m_stateActionCosts;
	std::vector<std::string> m_previousStateActions;
	std::string m_policyName;
};

