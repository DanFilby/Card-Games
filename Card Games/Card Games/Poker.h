#pragma once
#include	"Deck.h"
#include "Cards.h"

class PokerBoard {
public:
	PokerBoard(Deck&);
	void PrintBoard();
	void Flop();	//first three cards
	void Turn();	//fourth card
	void River();	//fifth card

private:
	Deck& deck;
	vector<Card> boardCards;

};

class PokerPlayer {
public:
	PokerPlayer();
	PokerPlayer(string _name, int _id, bool _player, int _startingCash);
	PokerPlayer(string _name, int _id, bool _player, int _startingCash,std::vector<Card>);
	void AddCard(Card);
	void AddCard(vector<Card>);
	void Clear();
	void Print();
	void Print(string Preface);
	vector<Card> cards;

private:
	string name;
	int id;
	bool isPlayer;
	int cash;

};

class PokerGame {
public:
	PokerGame(int numOp);
	void StartGame();
	void PrintPlayerHand();
	void PrintAllHands();

private:
	void Deal();
	Deck deck;
	PokerBoard board;
	PokerPlayer playerHand;
	vector<PokerPlayer> opponentsHands;

};