#include "PokerBoard.h"


PokerBoard::PokerBoard(CardDeck& deck) : boardDeck(deck){
	boardCards = vector<Card>();
	hands = vector<vector<Card>>();
}

void PokerBoard::PrintBoard() {
	PrintCards(boardCards);
}

void PokerBoard::AddHand(vector<Card> _hand){
	hands.push_back(_hand);
}

void PokerBoard::Flop() {
	for (int i = 0; i < 3; i++)
	{
		boardCards.push_back(boardDeck.DrawCard());
	}
}

void PokerBoard::Turn() {
	boardCards.push_back(boardDeck.DrawCard());
}

void PokerBoard::River() {
	boardCards.push_back(boardDeck.DrawCard());
}