#include "Deck.h"

Deck::Deck()
{
	//calls reset which adds all cards to a new deck
	Reset();
}

void Deck::Reset() {
	deck.clear();
	Suit suites[] = { Suit::Hearts, Suit::Diamonds, Suit::Spades, Suit::Clubs };

	//iterate over suits and add all cards of that suit to deck
	for (Suit s : suites) {
		//from 2 - ace, create the card and add to deck 
		for (int i = 2; i <= 14; i++)	
		{
			Card c = Card(s, i);
			deck.push_back(c);
		}
	}
}

Card Deck::Draw()
{
	return Card();
}

vector<Card> Deck::Draw(int num)
{
	return vector<Card>();
}

void Deck::Shuffle()
{
}

int Deck::Count()
{
	return 0;
}

void Deck::PrintCardsTopDown()
{
}
