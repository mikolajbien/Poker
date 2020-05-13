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

bool Hand::getCards(Card& cardOne, Card& cardTwo) const
{
	if (cardsInHand.size() == 0)
		return false;
	cardOne = Hand::cardsInHand[0];
	cardTwo = Hand::cardsInHand[1];
	return true;
}

std::vector<Card> Hand::getCardVector() const
{
	return Hand::cardsInHand;
}
