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

void Deck::Shuffle()
{
	std::shuffle(CardVector.begin(), CardVector.end(), rng);
}
