// Poker.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "stdafx.h"
#include "Deck.h"
#include "Player.h"
#include "Poker.h"

std::vector<Card> testVec = { Card(HEARTS, FIVE), Card(CLUBS, THREE), Card(SPADES, THREE), Card(DIAMONDS,FIVE), Card(DIAMONDS, FOUR), Card(HEARTS, FOUR),Card(HEARTS, FOUR) };
int main()
{
    
    Player player1;
    Deck testDeck(testVec);
    player1.DealToPlayer(testDeck);
    Poker testPoker(player1, testDeck, 5);
    bool test = testPoker.CheckFourOfAKind();
    bool test2 = testPoker.CheckThreeOfAKind();
}
//
