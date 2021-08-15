#include "Poker.h"
#include <algorithm>

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
	opponentsHands = vector<PokerPlayer>();
	
	//creates player object with id 1, starting cash and true for isplayer bool
	playerHand = PokerPlayer("player", 1, true, startingCash);
	for (int i = 1; i <= opponents; i++)
	{
		//creates opponents with generated name, id from 2-..., set starting cash and false to say not player
		//adds them to global vector
		string name = "Opponent " + std::to_string(i);
		PokerPlayer opponent = PokerPlayer(name, i + 1, false, startingCash);
		opponentsHands.push_back(opponent);
	}

	pot = PokerPot(opponentsHands);
}

void PokerGame::SetDefaultPlayerValues(int _startingCash)
{
	startingCash = _startingCash;
}

void PokerGame::StartGame()
{
	//Deal to player and all opponents
	Deal();
	PrintPlayerHand();
	pot.Bet(1, 100);
	pot.Bet(3, 1000);
	pot.PrintBets();
}

void PokerGame::PrintPlayerHand()
{
	playerHand.PrintPlayer();
}

void PokerGame::PrintOpponentsHands()
{
	for (int i = 1; i <= opponentsHands.size(); i++) {
		string preface = "Opponent-" + std::to_string(i) + ": ";
		opponentsHands[i - 1].PrintPlayer();
	}
}

void PokerGame::PrintAllHands()
{
	PrintPlayerHand();
	PrintOpponentsHands();
}

void PokerGame::Deal()
{
	for (int i = 0; i < 2; i++) {
		playerHand.AddCard(deck.Draw());
		for (PokerPlayer& opponent : opponentsHands) {
			opponent.AddCard(deck.Draw());
		}
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
	totalCash = 0;
	//default names for players
	names = { "none","player","Opponent-1","Opponent-2" ,"Opponent-3" ,"Opponent-4" ,"Opponent-5" ,"Opponent-6"
				,"Opponent-7" ,"Opponent-8" ,"Opponent-9" ,"Opponent-10" };
}

PokerPot::PokerPot(vector<PokerPlayer> opponents)
{
	totalCash = 0;

	//names is a vector that stores the players names, the player id will match index of name
	//as the id start from 1 as player first two items are
	names = { "none","player" };
	for (auto opp : opponents) {
		names.push_back(opp.name);
	}

}


void PokerPot::Bet(int playerId, int betValue)
{
	playersBets.emplace(playerId, betValue);
}

void PokerPot::PrintBets()
{
	cout << "Bets: \n";
	for (auto player : playersBets) {
		cout << "id: " << player.first << " - " << names[player.first] << " | " << player.second << "\n";
	}
	cout << "\n";
}
#pragma endregion

#pragma endregion
