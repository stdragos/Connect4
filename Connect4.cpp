#include "Connect4.h"
#include<stdio.h>
#include<windows.h>

void Connect4::Run(uint64_t numberOfPlays)
{
	std::setlocale(LC_CTYPE, ".UTF8");
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	Board board;
	std::unique_ptr<IPlayer> firstPlayer = std::make_unique<AIPlayer>(board, "AI1", "RedPiece.txt");
	std::unique_ptr<IPlayer> secondPlayer = std::make_unique<HumanPlayer>("drgaos");

	/*std::unique_ptr<IPlayer> firstPlayer = std::make_unique<HumanPlayer>("drgaos");
	std::unique_ptr<IPlayer> secondPlayer = std::make_unique<AIPlayer>(board, "AI2", "YellowPiece.txt");*/

	/*std::unique_ptr<IPlayer> firstPlayer = std::make_unique<AIPlayer>(board, "AI1", "RedPiece.txt");
	std::unique_ptr<IPlayer> secondPlayer = std::make_unique<AIPlayer>(board, "AI2", "YellowPiece.txt");*/
	bool drawEnd = true;
	bool drawBoard = true;
	IPlayer* currentPlayer;
	IPlayer* nextPlayer;
	AIPlayer* player1,* player2;

	for (uint64_t currentPlay = 0; currentPlay < numberOfPlays; ++currentPlay)
	{
		if (currentPlay % 10000 == 0)
			std::cout << currentPlay << '\n';

		board.Reset();
		currentPlayer = firstPlayer.get();
		nextPlayer = secondPlayer.get();
		Board::Piece currentPiece = Board::Piece::Red;
		Board::Piece nextPiece = Board::Piece::Yellow;
		ConsoleRenderer renderer;

		bool isGameActive = true;
		while (isGameActive)
		{
			renderer.Draw(board, drawBoard);

			bool isInputOk = false;
			while (!isInputOk)
			{
				const uint8_t& position = currentPlayer->GetNextAction();
				if (board.CanInsertPiece(position))
				{
					board.InsertPiece(position, currentPiece);
					isInputOk = true;
				}
			}

			player1 = dynamic_cast<AIPlayer*>(currentPlayer);
			player2 = dynamic_cast<AIPlayer*>(nextPlayer);
			auto state = board.Check();

			switch (state)
			{
			case Board::State::None:
				std::swap(currentPlayer, nextPlayer);
				std::swap(currentPiece, nextPiece);
				break;
			case Board::State::Win:
				renderer.EndScreen(currentPlayer, board, drawEnd);

				if (player1)
					player1->FeedReward(1.f);

				if (player2)
					player2->FeedReward(0.f);

				isGameActive = false;
				break;
			case Board::State::Draw:
				renderer.EndScreen(currentPlayer, board, drawEnd);

				if (player1)
					player1->FeedReward(0.5f);
				
				if (player2)
					player2->FeedReward(0.5f);

				isGameActive = false;
				break;
			default:
				break;
			}
		}
	}
}
