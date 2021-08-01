#include <iostream>
#include "Cards.h"


int main()
{
    Card c(Suit::Hearts, 11);

    std::cout << c.Name();
}