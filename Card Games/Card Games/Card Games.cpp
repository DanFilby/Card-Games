#include <iostream>
#include "Cards.h"
#include "Deck.h"
#include "PokerGame.h"
#include "UserCom.h"

using namespace std;

int main()
{
    //string name = UserCom::GetString("Enter name");
    PokerGame game(3);
    game.StartGame();

}