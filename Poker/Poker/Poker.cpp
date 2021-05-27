#include <iostream>
#include "PokerHand.h"
#include "CardDeck.h"
#include "PokerBoard.h"
using namespace std;

void PlayerSetup();
void NewGame();

CardDeck deck = CardDeck();
PokerBoard board = PokerBoard(deck);
PokerHand playerHand = PokerHand();

int numOpponents;

//maps for the card struct to change the num value into string and enum of suit into string
const string Card::numMap[] = { "Two","Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace" };
const string Card::suitMap[] = { "Hearts", "Diamonds", "Spades", "Clubs" };

int main()
{
    NewGame();

    playerHand.PrintHand();

    vector<Card> test{ deck.DrawCard(), deck.DrawCard() };
    PokerHand hand = PokerHand(test);

    board.Flop();

}

void NewGame() {
    board.ResetBoard();
    PlayerSetup();
}

void PlayerSetup() {
    playerHand = PokerHand();
    board.AddHand(playerHand);

    cout << "Enter Number of opponents: ";
    cin >> numOpponents;
    cout << "\n\n";

    for (int i = 0; i < numOpponents; i++)
    {   
        PokerHand hand = PokerHand();
        board.AddHand(hand);
    }
    //deck.PrintCardsTopDown();
    board.Deal();
    board.PrintAllHands();
   // deck.PrintCardsTopDown();
}