#pragma once
#include	"Deck.h"
#include "Cards.h"

class PokerBoard {
public:
	PokerBoard(Deck&);
	void PrintBoard();
	void Flop();	//first three cards
	void Turn();	//fourth card
	void River();	//fifth card

private:
	Deck& deck;
	vector<Card> boardCards;

};

class PokerHand {


};

class PokerGame {
public:
	PokerGame();
	void StartGame();


private:
	Deck deck;
	PokerBoard board;
	PokerHand playerHand;
	vector<PokerHand> opponentsHands;

};