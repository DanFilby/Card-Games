#include "Poker.h"
#include <algorithm>

#pragma region pokerBoard
PokerBoard::PokerBoard(Deck& _deck):deck{_deck}
{
}

void PokerBoard::PrintBoard()
{
	PrintCards(boardCards, "Board : ");
}

void PokerBoard::Flop()
{
	vector<Card> cards = deck.Draw(3);//gets top 3 cards 
	boardCards.insert(boardCards.end(), cards.begin(), cards.end());//appends those cards to board
}

void PokerBoard::Turn()
{
	boardCards.push_back(deck.Draw());
}

void PokerBoard::River()
{
	boardCards.push_back(deck.Draw());
}
#pragma endregion


#pragma region PokerGame
PokerGame::PokerGame(int numOp) : board(deck)
{
	//initialise the deck and shuffle
	deck = Deck();
	deck.Shuffle();
	
	//clamps number of opponents in range of 1 - 10 then uses it to create the opponents poker hands in a vector
	int opponents = std::max(1, std::min(numOp, 10));
	opponentsHands = vector<PokerPlayer>(opponents);
	
	//TODO: create hands with vaiables

}

void PokerGame::StartGame()
{
	//Deal to player and all opponents
	Deal();
	PrintPlayerHand();
}

void PokerGame::PrintPlayerHand()
{
	playerHand.Print("Player: ");
}

void PokerGame::PrintAllHands()
{
	playerHand.Print("Player: ");
	for (int i = 1; i <= opponentsHands.size(); i++) {
		string preface = "Opponent-" + std::to_string(i) + ": ";
		opponentsHands[i - 1].Print(preface);
	}
}

void PokerGame::Deal()
{
	for (int i = 0; i < 2; i++) {
		playerHand.AddCard(deck.Draw());
		for (PokerPlayer& opponent : opponentsHands) {
			opponent.AddCard(deck.Draw());
		}
	}	
}
#pragma endregion


#pragma region PokerHand
PokerPlayer::PokerPlayer()
{
	cards = vector<Card>();;
}

PokerPlayer::PokerPlayer(string _name, int _id, bool _player, int _startingCash)
	:name{_name}, id{_id}, isPlayer{_player}, cash{_startingCash}
{
	cards = vector<Card>();
}

PokerPlayer::PokerPlayer(string _name, int _id, bool _player, int _startingCash, std::vector<Card> _cards)
	: name{ _name }, id{ _id }, isPlayer{ _player }, cash{ _startingCash }
{
	cards = _cards;
}

void PokerPlayer::AddCard(Card card)
{
	cards.push_back(card);
}

void PokerPlayer::AddCard(vector<Card> _cards)
{
	cards.insert(cards.end(), _cards.begin(), _cards.end());
}

void PokerPlayer::Clear()
{
	cards.clear();
}

void PokerPlayer::Print()
{
	PrintCards(cards, "Hand: ");
}

void PokerPlayer::Print(string Preface)
{
	PrintCards(cards,Preface);
}
#pragma endregion
