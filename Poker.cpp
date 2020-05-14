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

Poker::Poker(Player player, Deck deck, int amountOfFlopCards)
{
	gameDeck = deck;
	currentPlayer = player;
	for (int i = 0; i < amountOfFlopCards; i++) {
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

bool Poker::CheckFlush(std::vector<Card>& flushCards)
{
	std::vector<Card> tempVector = Poker::flopCards;//tempvector to store both hand cards and flop cards in one vector

	std::vector<Card> handvec = Poker::currentPlayer.getHand().getCardVector();

	tempVector.insert(tempVector.end(), handvec.begin(), handvec.end());
	int vecLength = tempVector.size();
	int numOccurencesOfSuit = 0;
	for (int i = 0; i < vecLength - 4; i++) {
		int tempNumOccurencesOfSuit = 0;
		
		for (int j = 0; j < vecLength; j++) {
			if (tempVector[i].Suit == tempVector[j].Suit) {
				numOccurencesOfSuit++;
				flushCards.push_back(tempVector[j]);
			}

			
		}
		if (tempNumOccurencesOfSuit > numOccurencesOfSuit) {
			numOccurencesOfSuit = tempNumOccurencesOfSuit;
		}
		else {
			flushCards.clear();//clear out the flushCards vector if there is not a flush with the card at hand
		}
	}
	if (numOccurencesOfSuit >= 5) {
		return true;
	}
	return false;
}

bool Poker::CheckThreeOfAKind()
{
	std::vector<Card> tempVector = Poker::flopCards;//tempvector to store both hand cards and flop cards in one vector

	std::vector<Card> handvec = Poker::currentPlayer.getHand().getCardVector();

	tempVector.insert(tempVector.end(), handvec.begin(), handvec.end());
	int vecLength = tempVector.size();

	for (int i = 0; i < vecLength - 2; i++) {
		int numOccurences = 0;
		int numCardsRemaining = vecLength;


		for (int j = 0; j < vecLength; j++) {

			if (tempVector[i].Type == tempVector[j].Type)
				numOccurences++;
			if (numOccurences == 3) {
				return true;
			}
		}
	}


	return false;


}

bool Poker::CheckOnePair()
{
	std::vector<Card> tempVector = Poker::flopCards;//tempvector to store both hand cards and flop cards in one vector

	std::vector<Card> handvec = Poker::currentPlayer.getHand().getCardVector();

	tempVector.insert(tempVector.end(), handvec.begin(), handvec.end());
	int vecLength = tempVector.size();

	for (int i = 0; i < vecLength - 1; i++) {
		int numOccurences = 0;
		int numCardsRemaining = vecLength;
		for (int j = 0; j < vecLength; j++) {

			if (tempVector[i].Type == tempVector[j].Type)
				numOccurences++;
			if (numOccurences == 2) {
				return true;
			}
		}
	}
	return false;
}
