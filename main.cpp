// Poker.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "stdafx.h"
#include "Deck.h"
#include "Player.h"
#include "Poker.h"

std::vector<Card> testVec = { Card(HEARTS, FOUR), Card(CLUBS, FOUR), Card(SPADES, FOUR), Card(DIAMONDS,FOUR), Card(DIAMONDS, SIX) };
int main()
{
    
    Player player1;
    Deck testDeck(testVec);
    player1.DealToPlayer(testDeck);
    Poker testPoker(player1, testDeck);
    bool test = testPoker.CheckFourOfAKind();
}
//
