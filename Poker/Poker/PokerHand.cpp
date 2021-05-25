#include "PokerHand.h"
#include<string>

PokerHand::PokerHand(std::vector<Card> _cards)
{
	cards = _cards;
}

void PokerHand::PrintHand() {
	PrintCards(cards);
}


int PokerHand::TotalHandValue() {
	int result = 0;
	for (Card c : cards) {
		result += c.number;
	}
	return result;
}