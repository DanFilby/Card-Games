#include "Poker.h"

#pragma region pokerBoard

PokerBoard::PokerBoard(Deck& _deck):deck{_deck}
{
}

void PokerBoard::PrintBoard()
{
	PrintCards(boardCards, "Board : ");
}

void PokerBoard::Flop()
{
	vector<Card> cards = deck.Draw(3);//gets top 3 cards 
	boardCards.insert(boardCards.end(), cards.begin(), cards.end());//appends those cards to board
}

void PokerBoard::Turn()
{
	boardCards.push_back(deck.Draw());
}

void PokerBoard::River()
{
	boardCards.push_back(deck.Draw());
}

#pragma endregion

PokerGame::PokerGame() : board(deck)
{
	deck = Deck();
	deck.Shuffle();
	
}

void PokerGame::StartGame()
{
	deck.PrintCardsTopDown();
	
	board.Flop();
	board.PrintBoard();

	deck.PrintCardsTopDown();
}
