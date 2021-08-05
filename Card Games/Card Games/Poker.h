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
public:
	PokerHand();
	PokerHand(std::vector<Card>);
	void AddCard(Card);
	void AddCard(vector<Card>);
	void Clear();
	void Print();
	vector<Card> cards;

};

class PokerGame {
public:
	PokerGame(int numOp);
	void StartGame();


private:
	Deck deck;
	PokerBoard board;
	PokerHand playerHand;
	vector<PokerHand> opponentsHands;

};