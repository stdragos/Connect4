#include "ConsoleRenderer.h"

void ConsoleRenderer::Draw(const Board& board, bool draw) const
{
	if (!draw)
		return;

	for (int i = 0; i < Board::kRows; ++i)
	{
		for (int j = 0; j < Board::kColumns; ++j)
		{
			if (board[{i, j}].has_value())
			{
				switch (board[{i, j}].value())
				{
				case Board::Piece::Yellow:
					//std::cout << "Y ";
					std::cout << "🟡 ";
					break;
				case Board::Piece::Red:
					//std::cout << "R ";
					std::cout << "🔴 ";
					break;
				default:
					break;
				}
			}
			else
			{
				std::cout << "⭕ ";
			}
		}
		std::cout << '\n';
	}
	std::cout << "\n\n";

}

void ConsoleRenderer::EndScreen(const IPlayer* player, const Board& board, bool draw) const
{
	if (!draw)
		return;
	Draw(board, true);
	std::cout << player->GetName() << " won!\n";
}

void ConsoleRenderer::EndScreen(const Board& board, bool draw) const
{
	if (!draw)
		return;
	Draw(board, true);
	std::cout << "There was a draw.\n";
}
