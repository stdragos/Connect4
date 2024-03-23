#include "IPlayer.h"

IPlayer::IPlayer(const std::string& name) :
	m_name{ name }
{}

const std::string& IPlayer::GetName() const
{
	return m_name;
}
