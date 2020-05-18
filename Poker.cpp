#include "stdafx.h"
#include "Poker.h"

void Poker::DealOutCards()
{
	std::vector<Player>::iterator it;
	for (it = Players.begin(); it != Players.end(); ++it) {
		it->DealToPlayer(this->gameDeck);
	}
}

HAND_RANKING Poker::EvaluateCurrentPlayerHand()
{
	std::vector<Card> temp;
	Card cardTemp(HEARTS,KING);
	if (Poker::CheckRoyalFlush())
		return HAND_RANKING::ROYAL_FLUSH;
	if (Poker::CheckStraightFlush(temp))
		return HAND_RANKING::STRAIGHT_FLUSH;
	if (Poker::CheckFourOfAKind())
		return HAND_RANKING::FOUR_OF_A_KIND;
	if (Poker::CheckFullHouse(cardTemp, cardTemp))
		return HAND_RANKING::FULL_HOUSE;
	if (Poker::CheckFlush(temp))
		return HAND_RANKING::FLUSH;
	if (Poker::CheckStraight(temp))
		return HAND_RANKING::STRAIGHT;
	if (Poker::CheckThreeOfAKind(cardTemp))
		return HAND_RANKING::THREE_OF_A_KIND;
	if (Poker::CheckTwoPairs(cardTemp, cardTemp))
		return HAND_RANKING::TWO_PAIR;
	if (Poker::CheckOnePair())
		return HAND_RANKING::ONE_PAIR;
	
	return HAND_RANKING::HIGH_CARD;
}

//removes all instances of cards whose type matches in the specified parameter in the specified vector
void Poker::removeCards(TYPE_CARD type, std::vector<Card>& cardVec) const
{
	int vecLength = cardVec.size();
	for (int i = 0; i < vecLength; i++) {
		if (cardVec[i].Type == type) {
			cardVec.erase(cardVec.cbegin() + i);
			vecLength--;
			i--;
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

Poker::Poker(int amountOfFlopCards, int numPlayers)//TEST
{
	this->gameDeck = Deck();
	this->gameDeck.Shuffle();
	for (int i = 0; i < numPlayers; i++)
	{
		Players.push_back(Player());
	}
	DealOutCards();
	for (int i = 0; i < amountOfFlopCards; i++)
		flopCards.push_back(gameDeck.Deal());
	
	for (int i = 0; i < numPlayers; i++) {
		currentPlayer = Players[i];
		std::cout << (int)EvaluateCurrentPlayerHand() << std::endl;

	}
	
}

bool Poker::CheckRoyalFlush() const
{
	/*std::vector<Card> tempVector = Poker::flopCards;//tempvector to store both hand cards and flop cards in one vector	
	std::vector<Card> handvec = Poker::currentPlayer.getHand().getCardVector();
	tempVector.insert(tempVector.end(), handvec.begin(), handvec.end());*/
	std::vector<Card> flushCards;
	if (Poker::CheckStraightFlush(flushCards)) {
		int i = flushCards.size();
		if (flushCards[i].Type != ACE)
			return false;
		i--;
		if (flushCards[i].Type != KING)
			return false;
		i--;
		if (flushCards[i].Type != QUEEN)
			return false;
		i--;
		if (flushCards[i].Type != JACK)
			return false;
		i--;
		if (flushCards[i].Type != TEN)
			return false;
		return true;
	}
	else
		return false;
}

bool Poker::CheckStraightFlush(std::vector<Card> &straightflushCards) const
{
	std::vector<Card> vec;
	if (Poker::CheckStraight(vec) && Poker::CheckFlush(vec)) {
		straightflushCards = vec;
		std::stable_sort(straightflushCards.begin(), straightflushCards.end());
		return true;
	}
}

bool Poker::CheckFourOfAKind() const
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

bool Poker::CheckFullHouse(Card &tripletCard, Card &pairCard) const
{
	if (CheckThreeOfAKind(tripletCard)) {//run the checkThreeOfAKind Func
		std::vector<Card> tempVector = Poker::flopCards;//tempvector to store both hand cards and flop cards in one vector
		std::vector<Card> handvec = Poker::currentPlayer.getHand().getCardVector();
		tempVector.insert(tempVector.end(), handvec.begin(), handvec.end());
		
		Poker::removeCards(tripletCard.Type, tempVector);
		int vecLength = tempVector.size();
		bool pairFound = false;
		//loop to find a pair of cards in the remaining cards
		for (int i = 0; i < vecLength - 1; i++) {
			if (pairFound)
				break;
			int numOccurences = 0;

			for (int j = 0; j < vecLength; j++) {
				if (tempVector[i].Type == tempVector[j].Type) {
					numOccurences++;
					if (numOccurences == 2) {
						pairCard = tempVector[i];
						pairFound = true;
						break;
					}
				}
			}
		}
		if (pairFound) {//check for the possibility of a second pair that can be higher than the one we found
			for (int i = 0; i < vecLength - 1; i++) {
				if (tempVector[i].Type == pairCard.Type)//skip pair cards already found in prev loop
					continue;
				int numOccurences = 0;
				for (int j = 0; j < vecLength; j++) {
					if (tempVector[i].Type == tempVector[j].Type) {
						numOccurences++;
						if (numOccurences == 2) {
							if (tempVector[i].Type > pairCard.Type) {
								pairCard = tempVector[i];
								
							}
							goto PAIR_FOUND_LABEL;//easier than double break
							
						}
							
					}
				}
			}

			PAIR_FOUND_LABEL:return true;
		}
		else//no pair means no full house
			return false;
	}
	else {//no triplet means no full house
		return false;
	}
}

bool Poker::CheckFlush(std::vector<Card>& flushCards) const
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
				tempNumOccurencesOfSuit++;
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

bool Poker::CheckStraight(std::vector<Card>& straightCards) const
{
	std::vector<Card> tempVector = Poker::flopCards;//tempvector to store both hand cards and flop cards in one vector
	std::vector<Card> handvec = Poker::currentPlayer.getHand().getCardVector();
	tempVector.insert(tempVector.end(), handvec.begin(), handvec.end());
	int vecLength = tempVector.size();
	bool containsAce = false;
	for (int i = 0; i < vecLength; i++) {
		if (tempVector[i].Type == ACE) {
			containsAce = true;
			break;
		}
			
	}
	std::stable_sort(tempVector.begin(), tempVector.end());//sort the hand + flop vector by the type of card 
	int numCardsLeft = vecLength;
	int cardsInConsecutiveOrder = 1;
	for (int i = 0; i < vecLength - 1; i++) {
		if (cardsInConsecutiveOrder + numCardsLeft < 5) {//impossible for a straight to happen
			break;
		}
		if (((int)tempVector[i + 1].Type - (int)tempVector[i].Type) == 1) {
			cardsInConsecutiveOrder++;
		}
		else if (((int)tempVector[i + 1].Type - (int)tempVector[i].Type) > 1) {
			if (cardsInConsecutiveOrder >= 5)
				break;
			else
				cardsInConsecutiveOrder = 0;
		}
		numCardsLeft--;
	}
	if (cardsInConsecutiveOrder >= 5)
		return true;

	//IF ACE IS PRESENT
	if (containsAce) {
		for (int i = 0; i < vecLength; i++) {//loop to make ace lows
			if (tempVector[i].Type == ACE)
				tempVector[i].Type = ACE_LOW;
		}
		std::stable_sort(tempVector.begin(), tempVector.end());
		numCardsLeft = vecLength;
		cardsInConsecutiveOrder = 1;
		for (int i = 0; i < vecLength - 1; i++) {
			if (cardsInConsecutiveOrder + numCardsLeft < 5) {//impossible for a straight to happen
				break;
			}
			if (((int)tempVector[i + 1].Type - (int)tempVector[i].Type) == 1) {
				cardsInConsecutiveOrder++;
			}
			else if (((int)tempVector[i + 1].Type - (int)tempVector[i].Type) > 1) {
				if (cardsInConsecutiveOrder >= 5)
					break;
				else
					cardsInConsecutiveOrder = 0;
			}
			numCardsLeft--;
		}
		if (cardsInConsecutiveOrder >= 5) {
			return true;
		}
	}
	else {
		return false;
	}
	return false;
}

bool Poker::CheckThreeOfAKind(Card& threeOfAKindCard) const
{
	std::vector<Card> tempVector = Poker::flopCards;//tempvector to store both hand cards and flop cards in one vector
	std::vector<Card> handvec = Poker::currentPlayer.getHand().getCardVector();
	tempVector.insert(tempVector.end(), handvec.begin(), handvec.end());
	int vecLength = tempVector.size();
	bool threeOfAKindFound = false;
	for (int i = 0; i < vecLength - 2; i++) {
		int numOccurences = 0;
		//int numCardsRemaining = vecLength;
		

		for (int j = 0; j < vecLength; j++) {

			if (tempVector[i].Type == tempVector[j].Type) {
				
				numOccurences++;
				if (numOccurences == 3) {
					threeOfAKindCard = tempVector[i];
					threeOfAKindFound = true;
				}
			}
		}
		

	}
	Poker::removeCards(threeOfAKindCard.Type, tempVector);
	vecLength = tempVector.size();
	//checking to see if there is a higher three of a kind
	for (int i = 0; i < vecLength - 2; i++) {
		int numOccurences = 0;
		//int numCardsRemaining = vecLength;


		for (int j = 0; j < vecLength; j++) {

			if (tempVector[i].Type == tempVector[j].Type) {

				numOccurences++;
				if (numOccurences == 3) {
					if (tempVector[i].Type > threeOfAKindCard.Type) {
						threeOfAKindCard = tempVector[i];
						return true;
					}
				}
			}
		}


	}
	if (threeOfAKindFound)
		return true;
	return false;
}

bool Poker::CheckTwoPairs(Card &higherPairCard, Card &lowerPairCard) const
{
	std::vector<Card> tempVector = Poker::flopCards;//tempvector to store both hand cards and flop cards in one vector
	std::vector<Card> handvec = Poker::currentPlayer.getHand().getCardVector();

	tempVector.insert(tempVector.end(), handvec.begin(), handvec.end());
	int vecLength = tempVector.size();
	bool foundFirstPair = false;
	Card tempCard(HEARTS, ACE_LOW);
	for (int i = 0; i < vecLength - 1; i++) {
		if (foundFirstPair)
			break;//break out of outer loop
		int numOccurences = 0;
		
		for (int j = 0; j < vecLength; j++) {

			if (tempVector[i].Type == tempVector[j].Type)
				numOccurences++;
			if (numOccurences == 2) {
				foundFirstPair = true;
				tempCard = tempVector[i];
				break;//break out of inner loop
			}
		}
	}
	if (foundFirstPair) {
		Poker::removeCards(tempCard.Type, tempVector);
		vecLength = tempVector.size();
		for (int i = 0; i < vecLength - 1; i++) {
			int numOccurences = 0;
			for (int j = 0; j < vecLength; j++) {

				if (tempVector[i].Type == tempVector[j].Type)
					numOccurences++;
				if (numOccurences == 2) {
					if (tempVector[i].Type > tempCard.Type) {
						higherPairCard = tempVector[i];
						lowerPairCard = tempCard;
					}
					else {
						higherPairCard = tempCard;
						lowerPairCard = tempVector[i];
					}
					return true;
				}
			}
		}

	}
	return false;
}

bool Poker::CheckOnePair() const
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

Card Poker::EvaluateHighCard()
{
	std::vector<Card> tempVector = Poker::flopCards;//tempvector to store both hand cards and flop cards in one vector
	std::vector<Card> handvec = Poker::currentPlayer.getHand().getCardVector();
	tempVector.insert(tempVector.end(), handvec.begin(), handvec.end());
	std::stable_sort(tempVector.begin(), tempVector.end());//sort the hand + flop vector by the type of card
	return tempVector.back();
}
//static method that returns highest card in a given vector
Card Poker::EvaluateHighCard(std::vector<Card> cardVec)
{
	std::stable_sort(cardVec.begin(), cardVec.end());
	return cardVec.back();
}
