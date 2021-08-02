#include <iostream>
#include "Cards.h"
#include "Deck.h"

using namespace std;

int main()
{
    Deck d;
    d.Shuffle();
    
    vector<Card> c = d.Draw(54);

    for (auto f : c) {
        cout << f.Name();
    }
}