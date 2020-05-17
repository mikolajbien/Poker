// Poker.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "stdafx.h"
#include "Deck.h"
#include "Player.h"
#include "Poker.h"

std::vector<Card> testVec = {Card(HEARTS,NINE), Card(HEARTS,NINE),Card(SPADES,NINE),Card(HEARTS,SIX),Card(HEARTS,SIX),Card(HEARTS, SEVEN), Card(HEARTS, SEVEN) };
int main()
{
    
    Player player1;
    Deck testDeck(testVec);
    std::vector<Card> temp;
    player1.DealToPlayer(testDeck);
    Poker testPoker(player1, testDeck, 5);
    Card triplet(HEARTS, TWO);
    Card Pair(HEARTS, TWO);
    bool test2 = testPoker.CheckFullHouse(triplet, Pair);
    bool test = testPoker.CheckFourOfAKind();
   
    bool test3 = testPoker.CheckStraight(temp);
    bool test5 = testPoker.CheckFlush(temp);
    bool test4 = testPoker.CheckStraightFlush();
}
//
