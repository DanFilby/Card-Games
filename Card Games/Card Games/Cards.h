#pragma once

#include <string>
#include <iostream>
#include <vector>

using namespace std;

enum class Suit{ Hearts, Diamonds, Spades, Clubs };

const string CardValueMap[] = { "Two","Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace" };
const string SuitMap[] = { "Hearts", "Diamonds", "Spades", "Clubs" };

struct Card {
	Suit suit;
	short int value;

	Card() {
		suit = Suit::Hearts;
		value = 2;
	}

	Card(Suit _suit, int num) {
		suit = _suit;
		value = num - 2;
	}

	string Name() {
		return CardValueMap[value] + " Of " + SuitMap[(int)suit];
	}

};

static void PrintCards(vector<Card> cards, string preface) {
	if (cards.empty()) {
		return;
	}
	string result = "|  ";
	for (Card c : cards) {
		result += c.Name() + "  |  ";
	}
	cout << "\n" << preface << result << "\n\n";
}