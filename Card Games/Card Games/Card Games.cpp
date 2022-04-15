#include <iostream>
#include "Cards.h"
#include "Deck.h"
#include "PokerGame.h"
#include "UserCom.h"

using namespace std;

void evalTesting() {
	vector<PokerPlayer> players = {
				PokerPlayer("p1", 1, false, 1000, vector<Card>({ Card((Suit)0,2),Card((Suit)0,3) })),	//straight
				PokerPlayer("p2", 2, false, 1000, vector<Card>({ Card((Suit)3,2),Card((Suit)2,2) })),	//pair 2s
				PokerPlayer("p3", 3, false, 1000, vector<Card>({ Card((Suit)3,2),Card((Suit)3,8) }))	//diamond flush
	};

	std::vector<Card> boardsCards = { Card((Suit)1,4),Card((Suit)1,5),Card((Suit)1,6),Card((Suit)3,11),Card((Suit)3,10) };

	HandsEvaluator evaluator = HandsEvaluator(HandsEvaluator::EvalMethods::Optimized);
	std::vector<int> winnerid = evaluator.Evaluate(boardsCards, players);

	cout << winnerid[0];

}

int main()
{
	evalTesting();

    //string name = UserCom::GetString("Enter name");
    PokerGame game(3);
    game.StartGame();

}