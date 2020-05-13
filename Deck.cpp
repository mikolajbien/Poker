#include "stdafx.h"
#include "Deck.h"

Deck::Deck() {
	for (int suitEnum = HEARTS; suitEnum <= DIAMONDS; suitEnum++) {
		SUIT loopSuit = (SUIT)suitEnum;
		for (int cardTypeEnum = TWO; cardTypeEnum <= ACE; cardTypeEnum++) {
			TYPE_CARD loopType = (TYPE_CARD)cardTypeEnum;
			Card card(loopSuit, loopType);
			CardVector.push_back(card);
		}
	}
	std::random_device rd;//Random_device for true random numbers
	int seed = rd();
	this->rng.seed(seed);//Seed our RNG with a truly random number
	
}

Deck::Deck(std::vector<Card> copyVec)
{
	Deck::CardVector = copyVec;
}

void Deck::Shuffle()
{
	std::shuffle(CardVector.begin(), CardVector.end(), rng);
}

Card Deck::Deal()
{
	Card cardToDeal = CardVector.back();
	CardVector.pop_back();
	return cardToDeal;
}

void Deck::returnCardToDeck(Card CardToReturn)
{
	CardVector.push_back(CardToReturn);
}

