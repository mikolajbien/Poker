// Poker.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "stdafx.h"
#include "Deck.h"
#include "Player.h"
int main()
{
    int y{ 5 };
    Deck myDeck;
    myDeck.Shuffle();
    int x{ 5 };
    Card card1 = myDeck.Deal();
    Card card2 = myDeck.Deal();
    myDeck.returnCardToDeck(card1);
    myDeck.returnCardToDeck(card2);
    Player Player1;
    Player1.DealToPlayer(myDeck);
  
}
//
