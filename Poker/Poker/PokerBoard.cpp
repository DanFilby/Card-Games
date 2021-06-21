#include "PokerBoard.h"
#include "PokerHand.h"


PokerBoard::PokerBoard(CardDeck& deck) : boardDeck(deck){
	boardCards = vector<Card*>();
	hands = vector<PokerHand>();
}

void PokerBoard::ResetBoard()
{
	boardDeck.ResetDeck();
	boardDeck.Shuffle();
	boardCards.clear();
	hands.clear();
}

void PokerBoard::PrintBoard() {
	PrintCards(boardCards, "Board : ");
}

void PokerBoard::PrintAllHands()
{
	for (PokerHand h : hands)
	{
		cout << h.cards.size();
		h.PrintHand();
	}
}

void PokerBoard::AddHand(PokerHand& _hand){
	hands.push_back(_hand);
}

void PokerBoard::Deal()
{
	for (int i = 0; i < hands.size(); i++) {
		vector<Card*> newHand = vector<Card*>();
		newHand.push_back(boardDeck.DrawCard());
		newHand.push_back(boardDeck.DrawCard());
		copy(newHand.begin(), newHand.end(), hands[i].cards.begin());
	}
	
}

void PokerBoard::Flop() {
	for (int i = 0; i < 3; i++)
	{
		boardCards.push_back(boardDeck.DrawCard());
	}
	PrintBoard();
}

void PokerBoard::Turn() {
	boardCards.push_back(boardDeck.DrawCard());
	PrintBoard();
}

void PokerBoard::River() {
	boardCards.push_back(boardDeck.DrawCard());
	PrintBoard();
}