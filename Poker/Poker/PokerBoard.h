#include"Cards.h"
#include"CardDeck.h"
#include<iostream>
#include<vector>
using namespace std;

#pragma once
class PokerBoard
{
public:
	PokerBoard(CardDeck&);
	void PrintBoard();
	void AddHand(vector<Card>);
	void Flop();	//first three cards
	void Turn();	//fourth card
	void River();	//fifth card

private:
	CardDeck& boardDeck;
	vector<Card> boardCards;
	vector<vector<Card>> hands;
};

