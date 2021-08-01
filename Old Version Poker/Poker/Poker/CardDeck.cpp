#include "CardDeck.h"
#include<iostream>
#include <algorithm>
#include <random>

void CardDeck::ResetDeck() {
	deck.clear();
	Suit suites[] = { Suit::Hearts, Suit::Diamonds, Suit::Spades, Suit::Clubs };

	for (Suit s : suites) {
		for (int i = 2; i < 15; i++)
		{
			Card c = Card(s, i);
			deck.push_back(c);			
		}
	}
}

CardDeck::CardDeck() {
	ResetDeck();
}

int CardDeck::Size() {
	return deck.size();
}

void CardDeck::PrintCardsTopDown() {
	for (Card c : deck)
	{
		std::cout << c.Name() << "\n";
	}
}

Card* CardDeck::DrawCard(){
	Card* c = new Card(deck.back());
	deck.pop_back();
	return c;
}

void CardDeck::Shuffle() {
	std::random_device rd;	//random number device used as seed
	std::mt19937 g(rd());	//a better random number algorithm taking the random device as seed

	std:shuffle(deck.begin(), deck.end(), g);
}