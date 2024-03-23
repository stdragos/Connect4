#pragma once
#include <array>
#include <cstdint>
#include <optional>
#include <string>
class Board
{
public:
	enum class Piece
	{
		Yellow,
		Red
	};

	enum class State
	{
		None,
		Win,
		Draw
	};

	using Position = std::pair<uint8_t, uint8_t>;

public:
	static const uint8_t kColumns = 7;
	static const uint8_t kRows = 6;

public:
	void Reset();
	State Check() const;
	std::string GetBoardHash() const;

	std::array<std::array<std::optional<Board::Piece>, Board::kColumns>, Board::kRows>::const_iterator cbegin() const;
	std::array<std::array<std::optional<Board::Piece>, Board::kColumns>, Board::kRows>::const_iterator cend() const;

	std::optional<Piece>& operator[](const Position&);
	const std::optional<Piece>& operator[](const Position&) const;

	void InsertPiece(uint8_t, Piece);
	bool CanInsertPiece(uint8_t) const;
private:
	std::array<std::array<std::optional<Board::Piece>, Board::kColumns>, Board::kRows> m_board;
};

