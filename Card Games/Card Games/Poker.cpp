#include "Poker.h"
#include "UserCom.h"


#pragma region Poker

#pragma region Board
PokerBoard::PokerBoard(Deck& _deck):deck{_deck}
{
}

PokerBoard::PokerBoard(Deck& _deck, vector<Card> startCards) : deck{_deck }
{
	if (startCards.size() == 5) {
		boardCards = startCards;
	}
}

void PokerBoard::PrintBoard()
{
	PrintCards(boardCards, "Board : ");
}

void PokerBoard::NextRound()
{
	if (round == 1) {
		Flop();
	}
	else if (round == 2) {
		Turn();
	}
	else if (round == 3) {
		River();
	}

	PrintBoard();
	round++;
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
vector<Card> PokerBoard::BoardCards()
{
	return boardCards;
}
#pragma endregion


#pragma region Game

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

void PokerPot::NewRound() {
	lastRoundBet += currentBet; 
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
			((currentBet < playersNewTotal) ? " To raise to " : " To call to ") << (playersNewTotal - lastRoundBet) << "\n";
		
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
	cout << "Total Pot: " << totalCash << "  Current Bets: \n";
	for (auto player : playersBets) {
		cout << "id: " << player.first << " - " << names[player.first ] << " | " << player.second << "\n";
	}
	cout << "\n";
}
#pragma endregion

#pragma endregion
