#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(const std::string& name) :
    IPlayer{ name }
{}

uint8_t HumanPlayer::GetNextAction()
{
    std::cout << m_name << ", where do you want to put your piece?\nColumn: ";
    
    int column;
    std::cin >> column;

    std::cout << '\n';

    return column - 1;
}
