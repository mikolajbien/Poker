#pragma once
#include <random>
#include <algorithm>
#include "stdafx.h"
enum TYPE_CARD {ACE_LOW, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };
enum SUIT { HEARTS, CLUBS, SPADES, DIAMONDS };
struct Card {
	TYPE_CARD Type;
	SUIT Suit;
	Card() {//default constructor

	}
	Card(SUIT suit, TYPE_CARD type) {
		this->Suit = suit;
		this->Type = type;
	}
	bool operator<(Card c) const {//operator overload so sorting may be done
		if (this->Type < c.Type)
			return true;
		return false;
	}
};

class Deck {
private:
	std::vector<Card> CardVector;//Container for the Cards
	std::default_random_engine rng; //Random number generator for the Deck
	
public:
	Deck();
	Deck(std::vector<Card> copyVec);
	void Shuffle();
	Card Deal();
	void returnCardToDeck(Card CardToReturn);
};