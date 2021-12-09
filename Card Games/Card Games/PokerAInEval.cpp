#include "PokerAInEval.h"
#include <algorithm>

HandsEvaluator::HandsEvaluator(EvalMethods _evalMethod)
{
	ChangeEvalMethod(_evalMethod);
}

void HandsEvaluator::ChangeEvalMethod(EvalMethods _evalMethod)
{
	//couldn't find a clean way to do this without turning methods to static
	//basically wanted the equivilent of delegates in c#. tried function pointers and function<>
}

vector<int> HandsEvaluator::Evaluate(vector<Card> _boardCards, vector<PokerPlayer> _players)
{
	boardCards = _boardCards;
	players = _players;
	return Optimized();
}

vector<int> HandsEvaluator::BruteForce()
{
	return  vector<int>();

}

vector<int> HandsEvaluator::Optimized()
{
	vector<int> currentWinnerIds = FlushCheck();
	vector<int> idBuffer;

	if (!currentWinnerIds.empty()) {	//Flush present
		idBuffer = Intersection(currentWinnerIds, StraightCheck());	//straight flush ids are found here
		if (!idBuffer.empty()) {	//any straight flushes present
			//TODO:need to check for royal flush
			return currentWinnerIds;
		}
	}
	else {
		currentWinnerIds = StraightCheck();
	}

	int numOfKind = 0;
	idBuffer = HighestOfKind(numOfKind);

	if (numOfKind == 4) {
		return idBuffer;
	}
	if (numOfKind == 3) {
		if (!currentWinnerIds.empty()) {
			return currentWinnerIds;
		}
		else { return idBuffer; }
	}

}

vector<int> HandsEvaluator::FlushCheck()
{
	return vector<int>();
}

vector<int> HandsEvaluator::StraightCheck()
{
	return vector<int>();
}

vector<int> HandsEvaluator::HighestOfKind(int& _numOfKind)
{
	return vector<int>();
}

vector<int> HandsEvaluator::FullHouse()
{
	return vector<int>();
}

vector<int> HandsEvaluator::Intersection(vector<int> v1, vector<int> v2)
{
	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());
	
	vector<int> result;
	set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(result));
	return result;
}
