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
	vector<int> flushPlayers = vector<int>();

	for (auto p : players) {
		//stores a count of each suit
		int suitsCount[4] = {0,0,0,0};

		//add the boards card's suits
		for (auto c : boardCards) {
			suitsCount[(int)c.suit] += 1;
		}

		//add players cards suits
		suitsCount[(int)p.cards[0].suit] += 1;
		suitsCount[(int)p.cards[0].suit] += 1;

		//check for a flush in each suit
		for (int suitCount : suitsCount) {
			if (suitCount > 5) {
				flushPlayers.push_back(p.id);
			}
		}

	}
	return flushPlayers;
}

vector<int> HandsEvaluator::StraightCheck()
{
	//players with straight
	vector<int> straightPlayers = vector<int>();
	
	for (auto p : players) {
		//copy of the board cards ordered
		vector<Card> combinedBoard = vector<Card>(boardCards);
		combinedBoard.push_back(p.cards[0]);
		combinedBoard.push_back(p.cards[1]);
		std::sort(combinedBoard.begin(), combinedBoard.end(), [](Card a, Card b) { return a.value < b.value; });

		for (size_t i = 0; i < 2; i++)
		{
			int consecutiveCount = 0;
			int prevValue = combinedBoard[i].value;

			int j = i + 1;
			for (j; j < 4 + i; j++)
			{
				if (combinedBoard[j].value == ++prevValue) {
					consecutiveCount++;
				}
				else {
					break;
				}			
			}
			if (consecutiveCount > 5) {
				straightPlayers.push_back(p.id);
			}
			//TODO: could add same player twice
			//TODO: extract the combined board function
		}
		
	}
	
	return straightPlayers;
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
