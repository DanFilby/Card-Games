#include "Poker.h"
#include "UserCom.h"
#include <algorithm>
#include <chrono>
#include <thread>

#pragma region Poker

#pragma region Board
PokerBoard::PokerBoard(Deck& _deck):deck{_deck}
{
}

void PokerBoard::PrintBoard()
{
	PrintCards(boardCards, "Board : ");
}

void PokerBoard::Flop()
{
	vector<Card> cards = deck.Draw(3);//gets top 3 cards 
	boardCards.insert(boardCards.end(), cards.begin(), cards.end());//appends those cards to board
}

void PokerBoard::Turn()
{
	boardCards.push_back(deck.Draw());
}

void PokerBoard::River()
{
	boardCards.push_back(deck.Draw());
}
#pragma endregion


#pragma region Game
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
	do{
		if (UserCom::YesNo("Start Round?")) {
			continueGame = true;	
			NewRound();
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
	Blind();
	Deal();
	PrintPlayerHand();
	pot.PrintBets();

	PlayRound();

	//resets deck, hands, pot and increment dealer position
	Reset();
	pot.Reset();
	dealerIndex = (dealerIndex++) % players.size();
}

void PokerGame::PlayRound()
{
	bool goNextRound = false;
	int i = 0;
	while (!goNextRound) {
		//gets the player thats one after the dealer
		PokerPlayer currentPlayer = players[(i + dealerIndex + 1) % players.size()];

		cout << "\n " << currentPlayer.name << "  status " << (int)currentPlayer.status;
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
					cout << currentPlayer.name << " Folds!\n" << "  status is: " << (int)currentPlayer.status;
				}
				else if (aiChoice == 2) {//Call/Check
					pot.Call(currentPlayer);
				}
				else if (aiChoice == 3) {//Raise by 100
					pot.Bet(currentPlayer, pot.currentBet + 100 - pot.PlayersTotalBets(currentPlayer.id));
				}
			}
			cout << "\n";
		}

		//makes sure statuses are up to date and moves counter to next player. also c
		UpdatePlayerStatuses(goNextRound);
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
			cout << "checlking g ";	//TODO not working
		}

		else if (_player.status != PlayingStatus::Folded && pot.AmountToCall(_player.id) > 0) {	//players that are active and are behind the bet
			_player.status = PlayingStatus::Behind; 
			nextRoundCheck = false;	//as there are still players to bet or fold the round goes on
		}	
		else if(_player.status != PlayingStatus::Folded){	//players who have called or checked 
			_player.status = PlayingStatus::Called;
		}
	}
}

void PokerGame::Blind()
{
	//small blind 1 place from dealer
	pot.Bet(players[(dealerIndex + 1) % players.size()], currentAnte / 2);
	//big blind 2 places from dealer
	pot.Bet(players[(dealerIndex + 2) % players.size()], currentAnte);
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

#pragma endregion


#pragma region Player

//initsialise a player without giving values
PokerPlayer::PokerPlayer()
{
	//default values
	cards = vector<Card>();
	name = "Blank";
	id = 100;
	isPlayer = false;
	cash = 1000;
}

//initialise a player with empty hand and member values
PokerPlayer::PokerPlayer(string _name, int _id, bool _player, int _startingCash)
	:name{_name}, id{_id}, isPlayer{_player}, cash{_startingCash}
{
	cards = vector<Card>();
}

//initialise a player with a given hand and member values
PokerPlayer::PokerPlayer(string _name, int _id, bool _player, int _startingCash, std::vector<Card> _cards)
	: name{ _name }, id{ _id }, isPlayer{ _player }, cash{ _startingCash }
{
	cards = _cards;
}

//add a card to players hand
void PokerPlayer::AddCard(Card card)
{
	if (cards.size() + 1 > 2) { throw "Exceeds card limit"; }
	cards.push_back(card);
}

//add more than one card to players hand in vector form
void PokerPlayer::AddCard(vector<Card> _cards)
{
	cards.insert(cards.end(), _cards.begin(), _cards.end());
}

//clear players hand
void PokerPlayer::Clear()
{
	cards.clear();
}

//print players hand
void PokerPlayer::PrintHand()
{
	PrintCards(cards, "Hand: ");
}

//print players name, cash and cards 
void PokerPlayer::PrintPlayer()
{
	cout << name << " - " << cash << " : ";
	PrintCards(cards);
	cout << "\n\n";

}
#pragma endregion

#pragma region Pot

PokerPot::PokerPot()
{
	//default names for players
	names = { "none","player","Opponent-1","Opponent-2" ,"Opponent-3" ,"Opponent-4" ,"Opponent-5" ,"Opponent-6"
				,"Opponent-7" ,"Opponent-8" ,"Opponent-9" ,"Opponent-10" };

}



void PokerPot::Reset()
{
	for (int i = 1; i < names.size(); i++) {
		playersBets[i] = 0;
	}
	currentBet = 0;
	totalCash = 0;
}

PokerPot::PokerPot(vector<PokerPlayer> players)
{
	//names is a vector that stores the players names, the player id will match index of name
	//as the id start from 1 the first element is null
	names = vector<string>{ "null" };
	for (auto opp : players) {
		names.push_back(opp.name);
	}

	//adds all players to map
	Reset();
}

bool PokerPot::Call(PokerPlayer& player)
{
	int betAmount = AmountToCall(player.id);
	return Bet(player, betAmount);
}

/// <summary>
/// Adds a bet to the pot for the given player. checks if it matches or raises current.
/// then takes that bet off player total
/// </summary>
/// <returns> true if bet matches current  </returns>
bool PokerPot::Bet(PokerPlayer& player, int betAmount)
{
	int playersNewTotal = playersBets[player.id] + betAmount;

	if (playersNewTotal < currentBet && player.cash < betAmount) { return false; }
	else {
		//displays a bet message, either saying to call or to raise
		cout << "--> " << player.name << " bets " << betAmount << 
			((currentBet < playersNewTotal) ? " To raise to " : " To call to ") << playersNewTotal << "\n";
		
		playersBets[player.id] = playersNewTotal;
		currentBet = playersNewTotal;
		player.cash -= betAmount;
		totalCash += betAmount;
		return true;
	}
}

int PokerPot::AmountToCall(int id)
{
	return currentBet - playersBets[id];
}

int PokerPot::PlayersTotalBets(int id) {
	return playersBets[id];
}

void PokerPot::PrintBets()
{
	cout << "Bets: \n";
	for (auto player : playersBets) {
		cout << "id: " << player.first << " - " << names[player.first ] << " | " << player.second << "\n";
	}
	cout << "\n";
}
#pragma endregion

#pragma endregion
