#pragma once
#include	"Deck.h"
#include "Cards.h"
#include<unordered_map>

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
	void PrintHand();
	void PrintPlayer();
	vector<Card> cards;

	int id;
	string name;
	bool isPlayer;
	int cash;
};

class PokerPot {
public:
	PokerPot();
	PokerPot(vector<PokerPlayer> opponents);
	void Bet(int playerId, int betValue);
	void PrintBets();
	int totalCash;

private:
	//store each players bets as <id, total bet>
	std::unordered_map<int, int> playersBets;
	vector<string> names;
};

class PokerGame {
public:
	PokerGame(int numOp);
	void SetDefaultPlayerValues(int startingCash);
	void StartGame();
	void PrintPlayerHand();
	void PrintOpponentsHands();
	void PrintAllHands();

private:
	int startingCash = 5000;
	void Deal();
	Deck deck;
	PokerBoard board;
	PokerPot pot;
	PokerPlayer playerHand;
	vector<PokerPlayer> opponentsHands;

};