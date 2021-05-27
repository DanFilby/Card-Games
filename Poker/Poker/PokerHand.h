#pragma once
#include "Cards.h";
#include <iostream>
#include <vector>

class PokerHand
{
public:
	PokerHand();
	PokerHand(std::vector<Card>);
	static PokerHand NewEmptyHand();
	void AddCard(Card);
	void Clear();
	int TotalHandValue();
	void PrintHand();
	std::vector<Card> cards;
private:
	Card card1 = *new Card();
	Card card2 = *new Card();
	int cardSetterInt = 0;
};



