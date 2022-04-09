#include "PokerGame.h"

PokerGame::PokerGame(int numOp) : board(deck)
{
	//initialise the deck and shuffle
	deck = Deck();
	deck.Shuffle();

	//clamps number of opponents in range of 1 - 10 then uses it to create the opponents poker hands in a vector
	int opponents = std::max(1, std::min(numOp, 10));
	players = vector<PokerPlayer>();

	//creates player object with id 1, starting cash and true for isplayer bool
	PokerPlayer player = PokerPlayer("player", 1, true, startingCash);
	players.push_back(player);
	for (int i = 1; i <= opponents; i++)
	{
		//creates opponents with generated name, id from 2-..., set starting cash and false to say not player
		//adds them to global vector
		string name = "Opponent " + std::to_string(i);
		PokerPlayer opponent = PokerPlayer(name, i + 1, false, startingCash);
		players.push_back(opponent);
	}

	pot = PokerPot(players);

	//testing

	HandsEvaluator eval = HandsEvaluator(HandsEvaluator::EvalMethods::Optimized);
	//eval.Evaluate(board.BoardCards(), players);

}

void PokerGame::Reset()
{
	deck.Reset();
	for (PokerPlayer& player : players) {
		player.Clear();
	}

}

void PokerGame::SetDefaultPlayerValues(int _startingCash, int _startingAnte)
{
	startingCash = _startingCash;
	currentAnte = _startingAnte;
}

void PokerGame::StartGame()
{
	bool continueGame = false;
	do {
		if (UserCom::YesNo("Start Round?")) {
			Blind();
			Deal();
			continueGame = true;
			for (int i = 0; i < 4; i++) {	//4 rounds. intital betting, flop, turn and river
				board.NextRound();
				pot.NewRound();
				NewRound();
			}
			//work out winner
			dealerIndex = (dealerIndex++) % players.size();
			pot.Reset();
		}
		else {
			continueGame = false;
		}
	} while (continueGame);
	//TODO: add ending message
	cout << "Thanks for playing \n";
}

void PokerGame::Deal()
{
	for (int i = 0; i < 2; i++) {
		for (PokerPlayer& opponent : players) {
			opponent.AddCard(deck.Draw());
			opponent.status = PlayingStatus::Behind;
		}
	}
}

void PokerGame::NewRound()
{
	PrintPlayerHand();
	pot.PrintBets();

	PlayRound();
}

void PokerGame::PlayRound()
{
	//count of acive players
	int activePlayers = count_if(players.begin(), players.end(), [](PokerPlayer p) {return p.status != PlayingStatus::Folded; });

	bool goNextRound = false;
	int i = 0;
	while (!goNextRound) {
		//gets the player thats one after the dealer
		PokerPlayer& currentPlayer = players[(i + dealerIndex + 1) % players.size()];

		//the player is still in the current round
		if (currentPlayer.status != PlayingStatus::Folded) {
			//states who's turn it is to console
			cout << "==== " << currentPlayer.name << " Playing ====\n\n";
			cout << "To Call: " << pot.AmountToCall(currentPlayer.id) << "\n";

			//check if its the players turn 
			if (currentPlayer.isPlayer) {
				int playerDes = UserCom::PokerDecision(pot.AmountToCall(currentPlayer.id), currentPlayer.cash);
				if (playerDes == -1) {//Fold
					currentPlayer.status = PlayingStatus::Folded;
					cout << currentPlayer.name << " Folds!";
				}
				else if (playerDes == 0) {//Call/Check
					pot.Call(currentPlayer);
				}
				else if (playerDes > 0) {//Raise
					pot.Bet(currentPlayer, playerDes);
				}
			}
			else {	//a computer turn
				int aiChoice = rangeDistribution(rndEng);	//generate random int from 1,3
				if (aiChoice == 1) {//Fold
					currentPlayer.status = PlayingStatus::Folded;
					cout << currentPlayer.name << " Folds!\n";
				}
				else if (aiChoice == 2) {//Call/Check
					pot.Call(currentPlayer);
				}
				else if (aiChoice == 3) {//Raise by 100
					pot.Bet(currentPlayer, pot.currentBet + 100 - pot.PlayersTotalBets(currentPlayer.id));
				}
			}
			cout << "\n\n";
		}

		//if its looped over all active players it will
		//make sure statuses are up to date and moves counter to next player
		if (i >= players.size() - 1)UpdatePlayerStatuses(goNextRound);
		i++;
		this_thread::sleep_for(chrono::seconds(2));	//delay so player can read game messages
	}
}

/// <summary>
/// Updates the status of all active players. if the someone raised all non folded players'
/// statuses will be set to behind 
/// </summary>
void PokerGame::UpdatePlayerStatuses(bool& nextRoundCheck)
{
	//baseline it will be true but each loop checks for players that are behind on betting
	//which will make it false
	nextRoundCheck = true;
	for (PokerPlayer& _player : players) {
		if (_player.status == PlayingStatus::Folded) {
			continue;
		}
		if (pot.AmountToCall(_player.id) > 0) {		//players that are active and are behind the bet
			_player.status = PlayingStatus::Behind;
			nextRoundCheck = false;	//as there are still players to bet or fold the round goes on
		}
		else {										//players who have called or checked 
			_player.status = PlayingStatus::Called;
		}
	}
}

void PokerGame::Blind()
{
	cout << "Blinds:\n";
	//small blind 1 place from dealer
	pot.Bet(players[(dealerIndex + 1) % players.size()], currentAnte / 2);
	//big blind 2 places from dealer
	pot.Bet(players[(dealerIndex + 2) % players.size()], currentAnte);
	cout << "\n";
}

void PokerGame::PrintPlayerHand()
{
	for (auto pokerPlayer : players) {
		if (pokerPlayer.isPlayer) {
			pokerPlayer.PrintPlayer();
		}
	}
}

void PokerGame::PrintOpponentsHands()
{
	for (auto pokerPlayer : players) {
		if (!pokerPlayer.isPlayer) {
			pokerPlayer.PrintPlayer();
		}
	}
}

void PokerGame::PrintAllHands()
{
	for (auto pokerPlayer : players) {
		pokerPlayer.PrintPlayer();
	}
}
