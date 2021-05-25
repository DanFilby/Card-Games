#include <iostream>
#include "PokerHand.h"
#include "CardDeck.h"
using namespace std;

//maps for the card struct to change the num value into string and enum of suit into string
const string Card::numMap[] = { "Two","Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace" };
const string Card::suitMap[] = { "Hearts", "Diamonds", "Spades", "Clubs" };

int main()
{
    int numPlayers;
    cout << "Enter Number of Players: ";
    cin >> numPlayers;

    CardDeck deck = CardDeck();
    cout << "\n\n";
   
    deck.Shuffle();

    vector<Card> test{ deck.DrawCard(), deck.DrawCard() };
    PokerHand hand = PokerHand(test);

    //TODO: not random 
    hand.PrintHand();

}

