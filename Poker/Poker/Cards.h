#pragma once
#include<string>
#include<iostream>
#include<vector>
using namespace std;

enum class Suit : unsigned char
{
	Hearts, Diamonds, Spades, Clubs
};

struct Card {
	const static string numMap[];
	const static string suitMap[];

	Suit suit;
	short int number;
	Card() {
		suit = Suit::Diamonds;
		number = 2;
	}

	Card(Suit _suit, int num) {
		suit = _suit;
		number = num - 2;
	}

	string Name() {
		return numMap[number] + " Of " + suitMap[(int)suit];
	}
};

static void PrintCards(vector<Card> cards) {
	string result = "|  ";
	for (Card c : cards) {
		result += c.Name() + "  |  ";
	}
	cout << result;
}
