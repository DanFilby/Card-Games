//Header contains all the evaluation and AI functions for poker

#pragma once
#include<functional>
#include "Poker.h"

class HandsEvaluator {
public: 
	enum class EvalMethods { BruteForce, Optimized };
	HandsEvaluator(EvalMethods _evalMethod);
	void ChangeEvalMethod(EvalMethods _evalMethod);
	int Evaluate(vector<Card> _boardCards, vector<PokerPlayer> _players);	//returns id of winner

private:
	function<int()> currentEvalMethod;

	static int BruteForce();
	static int Optimized();

	vector<Card> boardCards;
	vector<PokerPlayer> players;
};

