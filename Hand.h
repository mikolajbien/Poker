#pragma once
#include "stdafx.h"
#include "Deck.h"
#include "Player.h"
class Hand {
private:
	std::vector<Card> cardsInHand;
	Player Owner;
public:
	void addCards(Card cardOne, Card cardTwo);
	void RemoveCards(Card& cardOne, Card& cardTwo);

};