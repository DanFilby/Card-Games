#include "Deck.h"
#include<iostream>
#include <algorithm>
#include <random>

Deck::Deck()
{
	//calls reset which adds all cards to a new deck
	Fill();
}

void Deck::Fill() {
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

void Deck::Reset() {
	Fill();
	Shuffle();
}

Card Deck::Draw()
{
	Card c = deck.back();
	deck.pop_back();
	return c;
}

vector<Card> Deck::Draw(int num)
{
	vector<Card> cards;

	for (int i = 0; i < num; i++) {
		if (!deck.empty()) {
			cards.push_back(Draw());
		}
	}

	return cards;
}

void Deck::Shuffle()
{
	std::random_device rd;	//random number device used as seed
	std::mt19937 g(rd());	//a better random number algorithm taking the random device as seed

	std:shuffle(deck.begin(), deck.end(), g);
}

int Deck::Count()
{
	return deck.size();
}

void Deck::PrintCardsTopDown()
{
	for (Card c : deck)
	{
		std::cout << c.Name() << "\n";
	}
}
