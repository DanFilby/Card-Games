#include "pch.h"
#include "CppUnitTest.h"
#include <vector>
#include "../Card Games/Poker.h"
#include "../Card Games/PokerAInEval.h"
#include "../Card Games/Poker.cpp"
#include "../Card Games/PokerAInEval.cpp"
#include "../Card Games/deck.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HandEvaluationTesting
{
	TEST_CLASS(FlushCheck)
	{
	public:
		
		TEST_METHOD(flushCheck1_Hearts)
		{
			vector<PokerPlayer> players = {
				PokerPlayer("p1", 1, false, 1000, vector<Card>({ Card((Suit)0,10),Card((Suit)0,12) })),	//heart flush
				PokerPlayer("p2", 2, false, 1000, vector<Card>({ Card((Suit)3,3),Card((Suit)3,9) })),	//pair 3s
			};

			std::vector<Card> boardsCards = { Card((Suit)0,2),Card((Suit)1,3),Card((Suit)0,7),Card((Suit)0,8),Card((Suit)11,2) };

			HandsEvaluator evaluator = HandsEvaluator(HandsEvaluator::EvalMethods::Optimized);
			std::vector<int> winnerid = evaluator.Evaluate(boardsCards, players);

			Assert::AreEqual(winnerid[0], players[0].id);
		}
		TEST_METHOD(flushCheck2_Clubs)
		{
			vector<PokerPlayer> players = {
				PokerPlayer("p1", 1, false, 1000, vector<Card>({ Card((Suit)1,4),Card((Suit)1,9) })), //pair 4s
				PokerPlayer("p2", 2, false, 1000, vector<Card>({ Card((Suit)3,9),Card((Suit)3,10) })),	//club flush
				PokerPlayer("p3", 3, false, 1000, vector<Card>({ Card((Suit)0,7),Card((Suit)1,7) }))	//pair 7s
			};

			std::vector<Card> boardsCards = { Card((Suit)3,4),Card((Suit)3,8),Card((Suit)3,3),Card((Suit)0,2),Card((Suit)0,12) };

			HandsEvaluator evaluator = HandsEvaluator(HandsEvaluator::EvalMethods::Optimized);
			std::vector<int> winnerid = evaluator.Evaluate(boardsCards, players);

			Assert::AreEqual(winnerid[0], players[1].id);
		}
		TEST_METHOD(flushCheck3_AgainstStraight)
		{
			vector<PokerPlayer> players = {
				PokerPlayer("p1", 1, false, 1000, vector<Card>({ Card((Suit)0,2),Card((Suit)0,3) })),	//straight
				PokerPlayer("p2", 2, false, 1000, vector<Card>({ Card((Suit)3,2),Card((Suit)2,2) })),	//pair 2s
				PokerPlayer("p3", 3, false, 1000, vector<Card>({ Card((Suit)1,2),Card((Suit)1,8) }))	//diamond flush
			};

			std::vector<Card> boardsCards = { Card((Suit)1,4),Card((Suit)1,5),Card((Suit)1,6),Card((Suit)3,11),Card((Suit)3,10) };

			HandsEvaluator evaluator = HandsEvaluator(HandsEvaluator::EvalMethods::Optimized);
			std::vector<int> winnerid = evaluator.Evaluate(boardsCards, players);

			Assert::AreEqual(winnerid[0], players[2].id);
		}TEST_METHOD(flushCheck4_Against3kind)
		{
			vector<PokerPlayer> players = {
				PokerPlayer("p1", 1, false, 1000, vector<Card>({ Card((Suit)0,2),Card((Suit)1,2) })),	//three 2s
				PokerPlayer("p2", 2, false, 1000, vector<Card>({ Card((Suit)3,7),Card((Suit)3,12) })),	//club flush
				PokerPlayer("p3", 3, false, 1000, vector<Card>({ Card((Suit)0,8),Card((Suit)0,9) }))	//pair 8s
			};

			std::vector<Card> boardsCards = { Card((Suit)2,2),Card((Suit)3,4),Card((Suit)3,5),Card((Suit)3,10),Card((Suit)1,8) };

			HandsEvaluator evaluator = HandsEvaluator(HandsEvaluator::EvalMethods::Optimized);
			std::vector<int> winnerid = evaluator.Evaluate(boardsCards, players);

			Assert::AreEqual(winnerid[0], players[1].id);
		}

	};

	TEST_CLASS(StraightCheck) {
		TEST_METHOD(StraightCheck1) {

			vector<PokerPlayer> players = {
				PokerPlayer("p1", 1, false, 1000, vector<Card>({ Card((Suit)0,2),Card((Suit)0,3) })),	//straight
				PokerPlayer("p2", 2, false, 1000, vector<Card>({ Card((Suit)3,2),Card((Suit)2,2) })),	//pair 2s
				PokerPlayer("p3", 3, false, 1000, vector<Card>({ Card((Suit)3,2),Card((Suit)3,8) }))	//high 10
			};

			std::vector<Card> boardsCards = { Card((Suit)1,4),Card((Suit)1,5),Card((Suit)1,6),Card((Suit)3,11),Card((Suit)3,10) };

			HandsEvaluator evaluator = HandsEvaluator(HandsEvaluator::EvalMethods::Optimized);
			std::vector<int> winnerid = evaluator.Evaluate(boardsCards, players);

			Assert::AreEqual(winnerid[0], players[0].id);
		}
		TEST_METHOD(StraightCheck2) {

			vector<PokerPlayer> players = {
				PokerPlayer("p1", 1, false, 1000, vector<Card>({ Card((Suit)0,7),Card((Suit)0,8) })),	//straight
				PokerPlayer("p2", 2, false, 1000, vector<Card>({ Card((Suit)3,2),Card((Suit)2,2) })),	//pair 2s
				PokerPlayer("p3", 3, false, 1000, vector<Card>({ Card((Suit)3,2),Card((Suit)3,8) }))	
			};

			std::vector<Card> boardsCards = { Card((Suit)1,4),Card((Suit)1,5),Card((Suit)1,9),Card((Suit)3,11),Card((Suit)3,10) };

			HandsEvaluator evaluator = HandsEvaluator(HandsEvaluator::EvalMethods::Optimized);
			std::vector<int> winnerid = evaluator.Evaluate(boardsCards, players);

			Assert::AreEqual(winnerid[0], players[0].id);
		}
	};

	TEST_CLASS(NumOfKindCheck) {
		TEST_METHOD(FourOfKind) {

			vector<PokerPlayer> players = {
				PokerPlayer("p1", 1, false, 1000, vector<Card>({ Card((Suit)0,4),Card((Suit)3,4) })),	//four 4s
				PokerPlayer("p2", 2, false, 1000, vector<Card>({ Card((Suit)1,12),Card((Suit)0,8) })),	//straight
				PokerPlayer("p3", 3, false, 1000, vector<Card>({ Card((Suit)3,2),Card((Suit)3,8) }))	//flush
			};

			std::vector<Card> boardsCards = { Card((Suit)1,4),Card((Suit)2,4),Card((Suit)3,9),Card((Suit)3,11),Card((Suit)3,10) };

			HandsEvaluator evaluator = HandsEvaluator(HandsEvaluator::EvalMethods::Optimized);
			std::vector<int> winnerid = evaluator.Evaluate(boardsCards, players);

			Assert::AreEqual(winnerid[0], players[0].id);
		}
		TEST_METHOD(ThreeOfKind) {

			vector<PokerPlayer> players = {
				PokerPlayer("p1", 1, false, 1000, vector<Card>({ Card((Suit)0,7),Card((Suit)0,8) })),	//straight
				PokerPlayer("p2", 2, false, 1000, vector<Card>({ Card((Suit)3,2),Card((Suit)2,2) })),	//pair 2s
				PokerPlayer("p3", 3, false, 1000, vector<Card>({ Card((Suit)3,2),Card((Suit)3,8) }))
			};

			std::vector<Card> boardsCards = { Card((Suit)1,4),Card((Suit)1,5),Card((Suit)1,9),Card((Suit)3,11),Card((Suit)3,10) };

			HandsEvaluator evaluator = HandsEvaluator(HandsEvaluator::EvalMethods::Optimized);
			std::vector<int> winnerid = evaluator.Evaluate(boardsCards, players);

			Assert::AreEqual(winnerid[0], players[0].id);
		}
		TEST_METHOD(ThreeKindLoseToFlush) {

			vector<PokerPlayer> players = {
				PokerPlayer("p2", 2, false, 1000, vector<Card>({ Card((Suit)3,2),Card((Suit)2,2) })),	//pair 2s
				PokerPlayer("p3", 3, false, 1000, vector<Card>({ Card((Suit)3,5),Card((Suit)0,5) })),	//three of kind
				PokerPlayer("p1", 1, false, 1000, vector<Card>({ Card((Suit)1,7),Card((Suit)1,12) }))	//straight
			};

			std::vector<Card> boardsCards = { Card((Suit)1,4),Card((Suit)1,5),Card((Suit)1,9),Card((Suit)3,11),Card((Suit)3,10) };

			HandsEvaluator evaluator = HandsEvaluator(HandsEvaluator::EvalMethods::Optimized);
			std::vector<int> winnerid = evaluator.Evaluate(boardsCards, players);

			Assert::AreEqual(winnerid[0], players[2].id);
		}

	};

	TEST_CLASS(FullHouseCheck) {
		TEST_METHOD(FullHouse) {

			vector<PokerPlayer> players = {
				PokerPlayer("p1", 1, false, 1000, vector<Card>({ Card((Suit)0,4),Card((Suit)3,6) })),	//four 4s
				PokerPlayer("p2", 2, false, 1000, vector<Card>({ Card((Suit)1,9),Card((Suit)3,4) })),	//full house
				PokerPlayer("p3", 3, false, 1000, vector<Card>({ Card((Suit)3,2),Card((Suit)3,8) }))	//flush
			};

			std::vector<Card> boardsCards = { Card((Suit)1,4),Card((Suit)2,4),Card((Suit)3,9),Card((Suit)3,11),Card((Suit)3,10) };

			HandsEvaluator evaluator = HandsEvaluator(HandsEvaluator::EvalMethods::Optimized);
			std::vector<int> winnerid = evaluator.Evaluate(boardsCards, players);

			Assert::AreEqual(winnerid[0], players[1].id);
		}
		TEST_METHOD(FullHouseLose) {

			vector<PokerPlayer> players = {
				PokerPlayer("p1", 1, false, 1000, vector<Card>({ Card((Suit)0,7),Card((Suit)0,8) })),	//straight
				PokerPlayer("p2", 2, false, 1000, vector<Card>({ Card((Suit)3,2),Card((Suit)2,2) })),	//pair 2s
				PokerPlayer("p3", 3, false, 1000, vector<Card>({ Card((Suit)3,2),Card((Suit)3,8) }))
			};

			std::vector<Card> boardsCards = { Card((Suit)1,4),Card((Suit)1,5),Card((Suit)1,9),Card((Suit)3,11),Card((Suit)3,10) };

			HandsEvaluator evaluator = HandsEvaluator(HandsEvaluator::EvalMethods::Optimized);
			std::vector<int> winnerid = evaluator.Evaluate(boardsCards, players);

			Assert::AreEqual(winnerid[0], players[0].id);
		}

	};
}
