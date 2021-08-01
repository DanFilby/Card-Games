#pragma once
#include "Cards.h"

class Deck
{
public:
	Deck();
	void Reset();
	Card Draw();
	vector<Card> Draw(int num);
	void Shuffle();
	int Count();
	void PrintCardsTopDown();
private:
	vector<Card> deck;

};

