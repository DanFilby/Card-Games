#include "PokerHand.h"
#include<string>

PokerHand::PokerHand()
{
	cards = vector<Card*>(2);
}

PokerHand::PokerHand(std::vector<Card*> _cards)
{
	cards = _cards;
}

PokerHand PokerHand::NewEmptyHand()
{
	vector<Card*> cards = vector<Card*>(2);
	PokerHand hand = PokerHand(cards);
	return hand;
}

void PokerHand::AddCard(Card* _card)
{
	cards.push_back(_card);
	PrintHand();
}

void PokerHand::Clear()
{
	for (Card* c : cards)
	{
		delete(c);
	}
}

void PokerHand::PrintHand() {
	PrintCards(cards, "Hand : ");
}


int PokerHand::TotalHandValue() {
	/*int result = 0;
	for (Card* c : cards) {
		result += c->number();
	}*/
	return 1;
}