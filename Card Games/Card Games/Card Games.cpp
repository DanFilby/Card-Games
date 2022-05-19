#include <iostream>
#include "Cards.h"
#include "Deck.h"
#include "PokerGame.h"
#include "UserCom.h"

using namespace std;

void evalTesting() {
	vector<PokerPlayer> players = {
				PokerPlayer("p1", 1, false, 1000, vector<Card>({ Card((Suit)0,4),Card((Suit)3,4) })),	//four 4s
				PokerPlayer("p2", 2, false, 1000, vector<Card>({ Card((Suit)1,12),Card((Suit)0,8) })),	//straight
				PokerPlayer("p3", 3, false, 1000, vector<Card>({ Card((Suit)3,2),Card((Suit)3,8) }))	//flush
	};

	std::vector<Card> boardsCards = { Card((Suit)1,4),Card((Suit)2,4),Card((Suit)3,9),Card((Suit)3,11),Card((Suit)3,10) };

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