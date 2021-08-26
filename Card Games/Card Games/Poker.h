#pragma once
#include	"Deck.h"
#include "Cards.h"
#include <unordered_map>
#include <memory>
#include <random>
#include <functional>

//all states a player can be either folded(out), Called(in and on top of bets)
//behind(in and behind on bets)
enum class PlayingStatus { Folded, Called, Behind };

class PokerBoard {
public:
	PokerBoard(Deck&);
	void PrintBoard();
	void NextRound();
	void Flop();	//first three cards
	void Turn();	//fourth card
	void River();	//fifth card

private:
	Deck& deck;
	vector<Card> boardCards;
	int round = 0;	//keeps track of current round
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
	PlayingStatus status;
};

class PokerPot {
public:
	PokerPot();
	PokerPot(vector<PokerPlayer> players);
	bool Call(PokerPlayer& player);
	bool Bet(PokerPlayer& player, int betAmount);
	int AmountToCall(int id);
	int PlayersTotalBets(int id);
	void PrintBets();
	void NewRound();
	void Reset();

	int totalCash = 0;
	int currentBet = 0;

private:
	//store each players bets as <id, total bet>
	std::unordered_map<int, int> playersBets;
	vector<string> names;
	int lastRoundBet = 0;	//value of last rounds bet so can show players start at 0 the next round
};

class PokerGame {
public:
	PokerGame(int numOp);
	void Reset();
	void SetDefaultPlayerValues(int startingCash, int startingAnte);
	void StartGame();
	void NewRound();
	void PlayRound();
	void UpdatePlayerStatuses(bool & nextRoundCheck);
	void Blind();
	void PrintPlayerHand();
	void PrintOpponentsHands();
	void PrintAllHands();

private:
	int startingCash = 5000;
	int dealerIndex = 0;
	int currentAnte = 100;
	void Deal();
	Deck deck;
	PokerBoard board;
	PokerPot pot;
	vector<PokerPlayer> players;
	std::default_random_engine rndEng;
	std::uniform_int_distribution<> rangeDistribution {1,3};
};