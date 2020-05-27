#pragma once

#include "stdafx.h"
enum TYPE_CARD {ACE_LOW, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };
enum SUIT { HEARTS, CLUBS, SPADES, DIAMONDS };
struct Card {
	TYPE_CARD Type;
	SUIT Suit;
	
	Card(SUIT suit, TYPE_CARD type) {
		this->Suit = suit;
		this->Type = type;
	}
	bool operator<(Card c) const {//operator overload so sorting may be done
		if (this->Type < c.Type)
			return true;
		return false;
	}
	std::string toString() {//put the card into a string representation
		std::string result = "";
		result += "Type: ";
		
		switch (this->Type) {
		case TWO:
			result += "Two";
			break;
		case THREE:
			result += "Three";
			break;
		case FOUR:
			result += "Four";
			break;
		case FIVE:
			result += "Five";
			break;
		case SIX:
			result += "Six";
			break;
		case SEVEN:
			result += "Seven";
			break;
		case EIGHT:
			result += "Eight";
			break;
		case NINE:
			result += "Nine";
			break;
		case TEN:
			result += "Ten";
			break;
		case JACK:
			result += "Jack";
			break;
		case QUEEN:
			result += "Queen";
			break;
		case KING:
			result += "King";
			break;
		case ACE:
			result += "Ace";
			break;

		}
		result += "\nSuit: ";

		
		switch (this->Suit) {
		case HEARTS:
			result += "HEARTS";
			break;
		case CLUBS:
			result += "CLUBS";
			break;
		case SPADES:
			result += "SPADES";
			break;
		case DIAMONDS:
			result += "DIAMONDS";

		}

		return result;
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
	int GetRandomNumber(int upperBound);
};