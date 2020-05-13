#pragma once
#include "stdafx.h"
#include "Deck.h"

class Hand {
private:
	std::vector<Card> cardsInHand;
	
public:
	void addCards(Card cardOne, Card cardTwo);
	void RemoveCards(Card& cardOne, Card& cardTwo);
	bool getCards(Card& cardOne, Card& cardTwo) const;
	std::vector<Card> getCardVector() const;
};