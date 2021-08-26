#include "PokerAInEval.h"

HandsEvaluator::HandsEvaluator(EvalMethods _evalMethod)
{
	ChangeEvalMethod(_evalMethod);
}

void HandsEvaluator::ChangeEvalMethod(EvalMethods _evalMethod)
{
	switch (_evalMethod) {
	case(EvalMethods::BruteForce):
		currentEvalMethod = BruteForce;
		break;
	case(EvalMethods::Optimized):
		currentEvalMethod = Optimized;
		break;
	default:
		currentEvalMethod = BruteForce;
	}
}

int HandsEvaluator::Evaluate(vector<Card> _boardCards, vector<PokerPlayer> _players)
{
	boardCards = _boardCards;
	players = _players;
	return currentEvalMethod();
}

int HandsEvaluator::BruteForce()
{
	int g = 2231;
	return g;

}

int HandsEvaluator::Optimized()
{
	int g = 2231;
	return g;
}
