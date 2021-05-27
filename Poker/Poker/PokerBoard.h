#include"Cards.h"
#include"CardDeck.h"
#include"PokerHand.h"
#include<iostream>
#include<vector>
using namespace std;

#pragma once
class PokerBoard
{
public:
	PokerBoard(CardDeck&);
	void ResetBoard();
	void PrintBoard();
	void PrintAllHands();
	void AddHand(PokerHand&);
	void Deal();
	void Flop();	//first three cards
	void Turn();	//fourth card
	void River();	//fifth card

private:
	CardDeck& boardDeck;
	vector<Card> boardCards;
	vector<PokerHand> hands;
};

