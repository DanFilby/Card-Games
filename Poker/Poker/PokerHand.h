#pragma once
#include "Cards.h";
#include <iostream>
#include <vector>

class PokerHand
{
public:
	PokerHand();
	PokerHand(std::vector<Card*>);
	static PokerHand NewEmptyHand();
	void AddCard(Card*);
	void Clear();
	int TotalHandValue();
	void PrintHand();
	std::vector<Card*> cards;
private:
	int cardSetterInt = 0;
};



