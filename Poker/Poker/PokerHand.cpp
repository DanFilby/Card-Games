#include "PokerHand.h"
#include<string>

PokerHand::PokerHand()
{
	cards = vector<Card>(&card1, &card2);
}

PokerHand::PokerHand(std::vector<Card> _cards)
{
	cards = _cards;
}

PokerHand PokerHand::NewEmptyHand()
{
	vector<Card> cards = vector<Card>(2);
	PokerHand hand = PokerHand(cards);
	return hand;
}

void PokerHand::AddCard(Card _card)
{
	//TODO: keeps deleting after leaving scope nvm doest actually work wtf
	card2 =  _card;
	cardSetterInt = (cardSetterInt++) % 2;
	PrintHand();
}

void PokerHand::Clear()
{
	for (Card c : cards)
	{
		delete(&c);
	}
}

void PokerHand::PrintHand() {
	PrintCards(cards, "Hand : ");
}


int PokerHand::TotalHandValue() {
	int result = 0;
	for (Card c : cards) {
		result += c.number;
	}
	return result;
}