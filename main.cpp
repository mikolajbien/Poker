// Poker.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "stdafx.h"
#include "Deck.h"
#include "Player.h"
#include "Poker.h"

std::vector<Card> testVec = {Card(HEARTS,NINE), Card(HEARTS,NINE),Card(SPADES,NINE),Card(HEARTS,SIX),Card(HEARTS,SIX),Card(HEARTS, SEVEN), Card(HEARTS, SEVEN) };
int main()
{
    
   
    Poker poker(5, 8);
    std::vector<Player*> winners = poker.DetermineWinner();

    for (std::vector<Player*>::iterator it = winners.begin(); it != winners.end(); ++it)
        std::cout << (*it)->getName() << std::endl;
    //getchar();
}
//
