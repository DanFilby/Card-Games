#pragma once
#include "Cards.h";
#include <iostream>
#include <vector>

class PokerHand
{
public:
	PokerHand(std::vector<Card> cards);
	int TotalHandValue();
	void PrintHand();
	std::vector<Card> cards;

};



