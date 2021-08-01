#pragma once
#include<vector>;
#include"Cards.h";

class CardDeck
{
public: 
	CardDeck();
	void ResetDeck();
	Card* DrawCard();
	void Shuffle();
	int Size();
	void PrintCardsTopDown();

private:
	std::vector<Card> deck;
};

