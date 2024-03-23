#include "Board.h"

void Board::Reset()
{
	memset(&m_board, 0, sizeof(m_board));
}

Board::State Board::Check() const
{
	uint8_t emptyCells = 0;
	// -> si diagonale dar doar in jos!
	for (int i = 0; i < kRows; ++i)
	{
		for (int j = 0; j < kColumns; ++j)
		{
			if (m_board[i][j].has_value())
			{
				uint8_t streak = 1;
				//->
				for (uint8_t k = j + 1; k < kColumns; ++k)
				{
					
					if (m_board[i][k].has_value() && m_board[i][k] == m_board[i][j])
					{
						++streak;
					}
					else
					{
						break;
					}
					if (streak >= 4)
					{
						return State::Win;
					}
				}
				streak = 1;
				//diagonal to the left
				for (int k = 1; i + k < kRows && j - k >= 0; ++k)
				{
					
					if (m_board[i + k][j - k].has_value() && m_board[i + k][j - k] == m_board[i][j])
					{
						++streak;
					}
					else
					{
						break;
					}
					if (streak >= 4)
					{
						return State::Win;
					}
				}
				streak = 1;
				//diagonal to the right
				for (int k = 1; i + k < kRows && j + k < kColumns; ++k)
				{
					
					if (m_board[i + k][j + k].has_value() && m_board[i + k][j + k] == m_board[i][j])
					{
						++streak;
					}
					else
					{
						break;
					}
					if (streak >= 4)
					{
						return State::Win;
					}
				}
				streak = 1;
				//down
				for (uint8_t k = i + 1; k < kRows; ++k)
				{

					if (m_board[k][j].has_value() && m_board[k][j] == m_board[i][j])
					{
						++streak;
					}
					else
					{
						break;
					}
					if (streak >= 4)
					{
						return State::Win;
					}
				}
			}
			else
			{
				++emptyCells;
			}
		}
	}

	return (emptyCells != 0) ? State::None : State::Draw;
}

std::string Board::GetBoardHash() const
{
	std::string hash = "";
	for (const auto& line : m_board)
	{
		for (const auto& piece : line)
		{
			if (piece.has_value())
			{
				switch (piece.value())
				{
				case Piece::Yellow:
					hash += "1";
					break;
				case Piece::Red:
					hash += "2";
					break;
				default:
					break;
				}
			}
			else
				hash += "0";
		}
	}

	return hash;
}

std::array<std::array<std::optional<Board::Piece>, Board::kColumns>, Board::kRows>::const_iterator Board::cbegin() const
{
	return m_board.cbegin();
}

std::array<std::array<std::optional<Board::Piece>, Board::kColumns>, Board::kRows>::const_iterator Board::cend() const
{
	return m_board.cend();
}

std::optional<Board::Piece>& Board::operator[](const Position& position)
{
	return const_cast<std::optional<Piece>&>(std::as_const(*this)[position]);
}

const std::optional<Board::Piece>& Board::operator[](const Position& position) const
{
	return m_board[position.first][position.second];
}

void Board::InsertPiece(uint8_t column, Piece piece)
{
	for (uint8_t i = kRows - 1; i >= 0; --i)
	{
		if (!m_board[i][column].has_value())
		{
			m_board[i][column] = piece;
			break;
		}
	}
}

bool Board::CanInsertPiece(uint8_t column) const
{
	if (column < 0 || column >= kColumns)
		return false;

	for (int i = static_cast<int>(kRows - 1); i >= 0; --i)
	{
		if (!m_board[i][column].has_value())
			return true;
	}
	return false;
}
