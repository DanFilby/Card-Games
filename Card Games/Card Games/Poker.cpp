#include "Poker.h"
#include <algorithm>

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

#pragma region PokerGame
PokerGame::PokerGame(int numOp) : board(deck)
{
	deck = Deck();
	deck.Shuffle();
	
	//clamps number of opponents in range of 1 - 10
	int opponents = std::max(1, std::min(numOp, 10));
	opponentsHands = vector<PokerHand>();

	for (int i = 0; i < 2; i++) {
		playerHand.AddCard(deck.Draw());
		for (PokerHand opponentHand : opponentsHands) {
			opponentHand.AddCard(deck.Draw());
		}
	}

	playerHand.Print();
	for (auto hand : opponentsHands) {
		cout << "print";
		hand.Print();
	}

}

void PokerGame::StartGame()
{
	//playerHand.Print();

}
#pragma endregion

#pragma region PokerHand
PokerHand::PokerHand()
{
}

PokerHand::PokerHand(std::vector<Card> _cards)
{
	cards = _cards;
}

void PokerHand::AddCard(Card card)
{
	cards.push_back(card);
}

void PokerHand::AddCard(vector<Card> _cards)
{
	cards.insert(cards.end(), _cards.begin(), _cards.end());
}

void PokerHand::Clear()
{
	cards.clear();
}

void PokerHand::Print()
{
	PrintCards(cards,"Hand: ");
}
#pragma endregion
