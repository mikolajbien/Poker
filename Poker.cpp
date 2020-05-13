#include "stdafx.h"
#include "Poker.h"

void Poker::DealOutCards()
{
	for (Player p : Players) {
		if (!p.GetIsSittingOut()) {
			p.DealToPlayer(Poker::gameDeck);
		}
	}
}

Poker::Poker(Player player, Deck deck)
{
	gameDeck = deck;
	currentPlayer = player;
	for (int i = 0; i < 3; i++) {
		flopCards.push_back(gameDeck.Deal());
	}
}

bool Poker::CheckRoyalFlush()
{
	//std::vector<Card> tempVector;
	//tempVector = Poker::flopCards;
	return false;
}

bool Poker::CheckFourOfAKind()
{
	std::vector<Card> tempVector = Poker::flopCards;//tempvector to store both hand cards and flop cards in one vector
	
	std::vector<Card> handvec = Poker::currentPlayer.getHand().getCardVector();

	tempVector.insert(tempVector.end(), handvec.begin(), handvec.end());
	int vecLength = tempVector.size();
	
	for (int i = 0; i < vecLength - 3; i++) {
		int numOccurences = 0;
		int numCardsRemaining = vecLength;
		
		
		for (int j = 0; j < vecLength; j++) {

			if (tempVector[i].Type == tempVector[j].Type)
				numOccurences++;
			if (numOccurences == 4) {
				return true;
			}
		}
	}
	
	
	return false;
	

}
