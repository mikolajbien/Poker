// Poker.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "stdafx.h"
#include "Deck.h"
#include "Player.h"
#include "Poker.h"

std::vector<Card> testVec = {Card(HEARTS,SIX), Card(HEARTS,FIVE),Card(HEARTS,FOUR),Card(HEARTS,THREE),Card(HEARTS,TWO), };
int main()
{
    
    Player player1;
    Deck testDeck(testVec);
    std::vector<Card> temp;
    player1.DealToPlayer(testDeck);
    Poker testPoker(player1, testDeck, 3);
    bool test = testPoker.CheckFourOfAKind();
    bool test2 = testPoker.CheckThreeOfAKind();
    bool test3 = testPoker.CheckStraight(temp);
}
//
