#pragma once
#include <random>
#include <algorithm>
#include "stdafx.h"
enum TYPE_CARD { TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };
enum SUIT { HEARTS, CLUBS, SPADES, DIAMONDS };
struct Card {
	TYPE_CARD Type;
	SUIT Suit;
	Card(SUIT suit, TYPE_CARD type) {
		this->Suit = suit;
		this->Type = type;
	}
};

class Deck {
private:
	std::vector<Card> CardVector;//Container for the Cards
	
	std::default_random_engine rng; //Random number generator for the Deck
	
public:
	Deck();
	void Shuffle();
};