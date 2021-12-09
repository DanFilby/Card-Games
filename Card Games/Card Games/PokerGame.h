#pragma once
#include "Deck.h"
#include "Cards.h"
#include "PokerAInEval.h"
#include "Poker.h"
#include "UserCom.h"
#include <unordered_map>
#include <memory>
#include <random>
#include <functional>
#include <algorithm>
#include <chrono>
#include <thread>

class PokerGame
{
public:
	PokerGame(int numOp);
	void Reset();
	void SetDefaultPlayerValues(int startingCash, int startingAnte);
	void StartGame();
	void NewRound();
	void PlayRound();
	void UpdatePlayerStatuses(bool& nextRoundCheck);
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
	std::uniform_int_distribution<> rangeDistribution{ 1,3 };

};

