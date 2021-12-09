#pragma once
#include<functional>
#include<vector>
#include"Poker.h"
//File contains all the evaluation and AI functions for poker

class HandsEvaluator {
public: 
	enum class EvalMethods { BruteForce, Optimized };
	HandsEvaluator(EvalMethods _evalMethod);
	void ChangeEvalMethod(EvalMethods _evalMethod);
	vector<int> Evaluate(vector<Card> _boardCards, vector<PokerPlayer> _players);	//returns id of winner

private:
	function<int()> currentEvalMethod;

	vector<int> BruteForce();
	vector<int> Optimized();

	vector<int> FlushCheck();
	vector<int> StraightCheck();
	vector<int> HighestOfKind(int& _numOfKind);
	vector<int> FullHouse();

	vector<int> Intersection(vector<int> v1, vector<int> v2);

	vector<Card> boardCards;
	vector<PokerPlayer> players;
};

