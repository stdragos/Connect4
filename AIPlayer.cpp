#include "AIPlayer.h"

std::random_device randomDevice;
std::mt19937 randomEngine(randomDevice());

const float initialEstimation = 0.5f;
const float explorationRate = 0.1f;
const float learningRate = 0.1f;

AIPlayer::AIPlayer(Board& board, const std::string& name, const std::string& policyName) :
	IPlayer(name), m_board{ board }, m_policyName{ policyName }
{
	LoadPolicy();
}

AIPlayer::~AIPlayer()
{
	SavePolicy();
}

uint8_t AIPlayer::GetNextAction()
{
	std::vector<uint8_t> possibleActions = GenerateActionCollection(m_board);
	uint8_t bestAction = possibleActions[0];
	std::string bestStateActionHash = "";
	std::string currentBoardHash = m_board.GetBoardHash();
	std::bernoulli_distribution bernDist(explorationRate);

	if (bernDist(randomEngine))
	{
		std::uniform_int_distribution<uint64_t> uniformDist(0, possibleActions.size() - 1);
		bestAction = possibleActions[uniformDist(randomEngine)];
		bestStateActionHash = currentBoardHash + std::to_string(bestAction);
		auto itMap = m_stateActionCosts.insert({ bestStateActionHash, initialEstimation });
	}
	else
	{
		float bestActionEstimation = -std::numeric_limits<float>::infinity();

		for (auto& action : possibleActions)
		{
			std::string stateActionHash = currentBoardHash + std::to_string(action);
			auto itMap = m_stateActionCosts.insert(std::make_pair(stateActionHash, initialEstimation));
			float currentActionEstimation = itMap.first->second;
			if (currentActionEstimation > bestActionEstimation)
			{
				bestAction = action;
				bestStateActionHash = stateActionHash;
				bestActionEstimation = currentActionEstimation;
			}
		}
	}

	m_previousStateActions.emplace_back(bestStateActionHash);
	return bestAction;
}

void AIPlayer::FeedReward(float target)
{
	for (auto it = m_previousStateActions.rbegin(); it != m_previousStateActions.rend(); ++it)
	{
		const auto& stateAction = *it;
		float& estimation = m_stateActionCosts[stateAction];
		estimation = estimation + learningRate * (target - estimation);
		target = estimation;
	}

	m_previousStateActions.clear();
}

std::vector<uint8_t> AIPlayer::GenerateActionCollection(const Board& board)
{
	std::vector<uint8_t> possibleActions;

	for (uint8_t i = 0; i < Board::kColumns; ++i)
	{
		if (board.CanInsertPiece(i))
		{
			possibleActions.emplace_back(i);
		}
	}

	return possibleActions;
}

void AIPlayer::SavePolicy() const
{
	std::ofstream out(m_policyName);

	for (const auto& pair : m_stateActionCosts)
		if (pair.second != initialEstimation)
			out << pair.first << ' ' << pair.second << '\n';

	out.close();
}

void AIPlayer::LoadPolicy()
{
	std::ifstream in(m_policyName);
	if (in.fail())
		return;

	std::string stateActionHash;
	float estimation;
	while (in >> stateActionHash >> estimation)
	{
		m_stateActionCosts[stateActionHash] = estimation;
	}

	in.close();
}
