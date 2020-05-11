#include "stdafx.h"
#include "Hand.h"

void Hand::addCards(Card cardOne, Card cardTwo)
{
	cardsInHand.push_back(cardOne);
	cardsInHand.push_back(cardTwo);
}

void Hand::RemoveCards(Card& cardOne, Card& cardTwo)
{
	cardOne = cardsInHand.back();
	cardsInHand.pop_back();
	cardTwo = cardsInHand.back();
	cardsInHand.pop_back();
}
