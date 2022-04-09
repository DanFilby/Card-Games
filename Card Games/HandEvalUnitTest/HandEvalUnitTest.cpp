#include "pch.h"
#include "CppUnitTest.h"
#include "../Card Games/Cards.h"
#include "../Card Games/Poker.h"
#include "../Card Games/PokerAInEval.h"
#include "../Card Games/Deck.h"
#include<vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HandEvalUnitTest
{
	TEST_CLASS(HandEvalUnitTest)
	{
	public:
		
		TEST_METHOD(flushCheck)
		{
			//Deck cardDeck = Deck();
			vector<PokerPlayer> players = vector<PokerPlayer>();

			std::vector<Card> p1Hand = { Card((Suit)1,2),Card((Suit)1,2) };
			std::vector<Card> p2Hand = { Card((Suit)3,2),Card((Suit)3,2) };

			PokerPlayer p1 = PokerPlayer("p1", 1, false, 1000, p1Hand);
			PokerPlayer p2 = PokerPlayer("p2", 2, false, 1000, p2Hand);

			players.push_back(p1);
			players.push_back(p2);

			std::vector<Card> boardsCards = { Card((Suit)1,2),Card((Suit)1,2),Card((Suit)1,2),Card((Suit)2,2),Card((Suit)1,2) };

			//PokerBoard board = PokerBoard(cardDeck, boardsCards);

			HandsEvaluator evaluator = HandsEvaluator(HandsEvaluator::EvalMethods::Optimized);
			std::vector<int> winnerid = evaluator.Evaluate(boardsCards, players);

			Assert::AreEqual(winnerid[0], p1.id);
		}
	};
}
