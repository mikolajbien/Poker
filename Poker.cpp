#include "stdafx.h"
#include "Poker.h"

void Poker::DealOutCards()
{
	std::vector<Player>::iterator it;
	for (it = Players.begin(); it != Players.end(); ++it) {
		it->DealToPlayer(this->gameDeck);
	}
}


//this method ranks each players hands including tiebreaking measures
HAND_RANKING Poker::EvaluateCurrentPlayerHand()
{
	std::vector<Card> temp;
	Card cardTemp(HEARTS, KING);
	Card cardTemp2(CLUBS, KING);
	Ranking rank((this->currentPlayer));
	if (Poker::CheckRoyalFlush()) {
		rank.rankOfHand = HAND_RANKING::ROYAL_FLUSH;
		handRankings.push_back(rank);
		return HAND_RANKING::ROYAL_FLUSH;
	}
	if (Poker::CheckStraightFlush(temp, cardTemp)) {
		rank.rankOfHand = HAND_RANKING::STRAIGHT_FLUSH;
		rank.tiebreakerCards.push_back(cardTemp.Type);
		handRankings.push_back(rank);
		return HAND_RANKING::STRAIGHT_FLUSH;
	}
	if (Poker::CheckFourOfAKind()) {
		rank.rankOfHand = HAND_RANKING::FOUR_OF_A_KIND;
		rank.tiebreakerCards.push_back(cardTemp.Type);
		rank.tiebreakerCards.push_back(cardTemp2.Type);
		handRankings.push_back(rank);
		return HAND_RANKING::FOUR_OF_A_KIND;
	}
	if (Poker::CheckFullHouse(cardTemp, cardTemp2)) {
		rank.rankOfHand = HAND_RANKING::FULL_HOUSE;
		rank.tiebreakerCards.push_back(cardTemp.Type);//triplet
		rank.tiebreakerCards.push_back(cardTemp2.Type);//pair
		handRankings.push_back(rank);
		return HAND_RANKING::FULL_HOUSE;
	}
	if (Poker::CheckFlush(temp)) {
		rank.rankOfHand = HAND_RANKING::FLUSH;
		rank.tiebreakerCards.push_back(temp.back().Type);
		handRankings.push_back(rank);
		return HAND_RANKING::FLUSH;
	}
	if (Poker::CheckStraight(temp)) {
		rank.rankOfHand = HAND_RANKING::STRAIGHT;
		rank.tiebreakerCards.push_back(temp.back().Type);
		handRankings.push_back(rank);
		return HAND_RANKING::STRAIGHT;
	}
	if (Poker::CheckThreeOfAKind(cardTemp)) {
		rank.rankOfHand = HAND_RANKING::THREE_OF_A_KIND;
		rank.tiebreakerCards.push_back(cardTemp.Type);
		

		//determine high cards 
		std::vector<Card> handAndFlopVec = Poker::combineHandAndFlopCards();
		removeCards(cardTemp.Type, handAndFlopVec);
		std::sort(handAndFlopVec.begin(), handAndFlopVec.end());

		//push the two high cards possible in a three of a kind
		rank.tiebreakerCards.push_back(handAndFlopVec[handAndFlopVec.size() - 1].Type);//high card
		rank.tiebreakerCards.push_back(handAndFlopVec[handAndFlopVec.size() - 2].Type);//second highest high card
		handRankings.push_back(rank);


		return HAND_RANKING::THREE_OF_A_KIND;
	}
	if (Poker::CheckTwoPairs(cardTemp, cardTemp2)) {
		rank.rankOfHand = HAND_RANKING::TWO_PAIR;
		//value of the pairs will determine tiebreakers
		rank.tiebreakerCards.push_back(cardTemp.Type);
		rank.tiebreakerCards.push_back(cardTemp2.Type);

		//remove the pairs
		std::vector<Card> handAndFlopVec = Poker::combineHandAndFlopCards();
		Poker::removeCards(cardTemp.Type, handAndFlopVec);
		Poker::removeCards(cardTemp2.Type, handAndFlopVec);

		//add the kicker card needed for rare tiebreakers
		rank.tiebreakerCards.push_back(Poker::EvaluateHighCard(handAndFlopVec).Type);
		handRankings.push_back(rank);
		return HAND_RANKING::TWO_PAIR;
	}
	if (Poker::CheckOnePair(cardTemp)) {
		rank.rankOfHand = HAND_RANKING::ONE_PAIR;
		rank.tiebreakerCards.push_back(cardTemp.Type);

		//remove the pair
		std::vector<Card> handAndFlopVec = Poker::combineHandAndFlopCards();
		Poker::removeCards(cardTemp.Type, handAndFlopVec);

		//add the three kickers
		
		rank.tiebreakerCards.push_back(handAndFlopVec[handAndFlopVec.size() - 1].Type);//high card
		rank.tiebreakerCards.push_back(handAndFlopVec[handAndFlopVec.size() - 2].Type);//second highest high card
		rank.tiebreakerCards.push_back(handAndFlopVec[handAndFlopVec.size() - 3].Type);//third highest

		handRankings.push_back(rank);
		return HAND_RANKING::ONE_PAIR;
	}

	//IF NO PAIRS are found
	std::vector<Card> handAndFlopVec = Poker::combineHandAndFlopCards();
	std::stable_sort(handAndFlopVec.begin(), handAndFlopVec.end());

	rank.tiebreakerCards.push_back(handAndFlopVec[handAndFlopVec.size() - 1].Type);//high card
	rank.tiebreakerCards.push_back(handAndFlopVec[handAndFlopVec.size() - 2].Type);//second highest high card
	rank.tiebreakerCards.push_back(handAndFlopVec[handAndFlopVec.size() - 3].Type);//third highest
	rank.tiebreakerCards.push_back(handAndFlopVec[handAndFlopVec.size() - 4].Type);//fourth highest
	rank.tiebreakerCards.push_back(handAndFlopVec[handAndFlopVec.size() - 5].Type);//fifth highest
	return HAND_RANKING::HIGH_CARD;
}

std::vector<Player*> Poker::DetermineWinner()
{
	std::vector<Player*> winners;
	std::stable_sort(handRankings.begin(), handRankings.end());//sort the rankings
	
	
	std::vector<Ranking>::iterator it = std::max_element(handRankings.begin(), handRankings.end());
	for (it; it != handRankings.end(); ++it)
		winners.push_back(it->Owner);
	return winners;
}
//



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

std::vector<Card> Poker::combineHandAndFlopCards() const
{
	std::vector<Card> result = this->flopCards;
	std::vector<Card> handvec = Poker::currentPlayer->getHand().getCardVector();
	result.insert(result.end(), handvec.begin(), handvec.end());
	
	return result;
}


Poker::Poker(int amountOfFlopCards, int numPlayers)//TEST
{
	this->gameDeck = Deck();
	this->gameDeck.Shuffle();
	//this->gameDeck = Deck({ Card(CLUBS, EIGHT),Card(HEARTS, SEVEN),Card(SPADES, JACK),Card(HEARTS, JACK), Card(DIAMONDS, FIVE),Card(SPADES, THREE),Card(DIAMONDS, ACE) ,Card(SPADES, QUEEN) ,Card(HEARTS, NINE), Card(CLUBS, KING), Card(CLUBS, NINE), Card(SPADES, FOUR), Card(CLUBS, TEN), Card(DIAMONDS, FOUR), Card(DIAMONDS, NINE) });
	for (int i = 0; i < numPlayers; i++)
	{
		std::string name = "player " + std::to_string(i);
		Players.push_back(Player(name));
	}
	DealOutCards();
	for (int i = 0; i < numPlayers; i++)
	{
		std::cout << "Player " + std::to_string(i) + "\nHand: " + Players[i].getHand().getCardVector()[0].toString() + "\n" + Players[i].getHand().getCardVector()[1].toString() << "\n" << std::endl;
	}
	for (int i = 0; i < amountOfFlopCards; i++)
		flopCards.push_back(gameDeck.Deal());
	std::cout << "FLOP CARDS" << std::endl;
	for (int i = 0; i < amountOfFlopCards; i++)
		std::cout << this->flopCards[i].toString() << std::endl;
	for (int i = 0; i < numPlayers; i++) {
		currentPlayer = &Players[i];
		std::cout << (int)EvaluateCurrentPlayerHand() << std::endl;

	}
	
}
//
bool Poker::CheckRoyalFlush() const
{
	/*std::vector<Card> tempVector = Poker::flopCards;//tempvector to store both hand cards and flop cards in one vector	
	std::vector<Card> handvec = Poker::currentPlayer.getHand().getCardVector();
	tempVector.insert(tempVector.end(), handvec.begin(), handvec.end());*/
	std::vector<Card> flushCards;
	Card temp(HEARTS, ACE_LOW);
	if (Poker::CheckStraightFlush(flushCards, temp)) {
		int i = flushCards.size() - 1;
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

bool Poker::CheckStraightFlush(std::vector<Card>& straightFlushCards, Card &highCard) const
{
	//
	if (Poker::CheckFlush(straightFlushCards)) {
		std::stable_sort(straightFlushCards.begin(), straightFlushCards.end());
		bool containsAce = false;
		for (int i = 0; i < straightFlushCards.size(); i++) {
			if (straightFlushCards[i].Type == ACE) {
				containsAce = true;
				break;
			}

		}
		
		int vecLength = straightFlushCards.size();
		int numCardsLeft = vecLength;
		int cardsInConsecutiveOrder = 1;
		for (int i = 0; i < vecLength - 1; i++) {
			
			if ((cardsInConsecutiveOrder + numCardsLeft) < 5) {//impossible for a straight to happen
				break;
			}
			if (((int)straightFlushCards[i + 1].Type - (int)straightFlushCards[i].Type) == 1) {
				
				cardsInConsecutiveOrder++;

			}
			else if (((int)straightFlushCards[i + 1].Type - (int)straightFlushCards[i].Type) > 1) {//if a card is not in consecutive order
				if (cardsInConsecutiveOrder >= 5)//straight is found
					break;
				else {//reset 
					cardsInConsecutiveOrder = 1;
					
				}
			}
			numCardsLeft--;
		}
		if (cardsInConsecutiveOrder >= 5) {
			highCard = straightFlushCards.back();
			return true;
		}

		if (containsAce) {//if an ace was found we have to check again with ace being low
			
			for (int i = 0; i < vecLength; i++) {//loop to make ace lows
				if (straightFlushCards[i].Type == ACE)
					straightFlushCards[i].Type = ACE_LOW;
			}
			std::stable_sort(straightFlushCards.begin(), straightFlushCards.end());
			numCardsLeft = vecLength;
			cardsInConsecutiveOrder = 1;
			for (int i = 0; i < vecLength - 1; i++) {
				if (cardsInConsecutiveOrder + numCardsLeft < 5) {//impossible for a straight to happen
					break;
				}
				if (((int)straightFlushCards[i + 1].Type - (int)straightFlushCards[i].Type) == 1) {
					cardsInConsecutiveOrder++;
				}
				else if (((int)straightFlushCards[i + 1].Type - (int)straightFlushCards[i].Type) > 1) {//if a card is not in consecutive order
					if (cardsInConsecutiveOrder >= 5)//straight is found
						break;
					else {//reset
						cardsInConsecutiveOrder = 1;
						
					}
				}
				numCardsLeft--;
			}
			if (cardsInConsecutiveOrder >= 5) {
				highCard = straightFlushCards.back();
				return true;
			}
		}
		else {
			return false;
		}
	}
	return false;
}
bool Poker::CheckFourOfAKind() const
{
	std::vector<Card> tempVector = Poker::flopCards;//tempvector to store both hand cards and flop cards in one vector	
	std::vector<Card> handvec = Poker::currentPlayer->getHand().getCardVector();
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
		std::vector<Card> handvec = Poker::currentPlayer->getHand().getCardVector();
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
	std::vector<Card> handvec = Poker::currentPlayer->getHand().getCardVector();
	tempVector.insert(tempVector.end(), handvec.begin(), handvec.end());
	int vecLength = tempVector.size();
	int numOccurencesOfSuit = 0;
	for (int i = 0; i < vecLength - 4; i++) {
		
		numOccurencesOfSuit = 0;
		
		for (int j = 0; j < vecLength; j++) {
			if (tempVector[i].Suit == tempVector[j].Suit) {
				numOccurencesOfSuit++;
				flushCards.push_back(tempVector[j]);
			}
		}
		if (numOccurencesOfSuit >= 5) {
			break;
		}
		else {
			flushCards.clear();//clear out the flushCards vector if there is not a flush with the card at hand
		}
	}
	if (numOccurencesOfSuit >= 5) {
		std::stable_sort(flushCards.begin(), flushCards.end());
		return true;
	}
	else
		return false;
}
//
bool Poker::CheckStraight(std::vector<Card>& straightCards) const
{
	std::vector<Card> tempVector = Poker::flopCards;//tempvector to store both hand cards and flop cards in one vector
	std::vector<Card> handvec = Poker::currentPlayer->getHand().getCardVector();
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
		if (cardsInConsecutiveOrder == 1)
			straightCards.push_back(tempVector[i]);
		if (cardsInConsecutiveOrder + numCardsLeft < 5) {//impossible for a straight to happen
			break;
		}
		if (((int)tempVector[i + 1].Type - (int)tempVector[i].Type) == 1) {
			straightCards.push_back(tempVector[i + 1]);
			cardsInConsecutiveOrder++;
			
		}
		else if (((int)tempVector[i + 1].Type - (int)tempVector[i].Type) > 1) {
			if (cardsInConsecutiveOrder >= 5)
				break;
			else {
				cardsInConsecutiveOrder = 1;
				straightCards.clear();
			}
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
					cardsInConsecutiveOrder = 1;
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
	std::vector<Card> handvec = Poker::currentPlayer->getHand().getCardVector();
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
	std::vector<Card> handvec = Poker::currentPlayer->getHand().getCardVector();

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

bool Poker::CheckOnePair(Card& pairCard) const
{
	std::vector<Card> tempVector = Poker::flopCards;//tempvector to store both hand cards and flop cards in one vector
	std::vector<Card> handvec = Poker::currentPlayer->getHand().getCardVector();
	tempVector.insert(tempVector.end(), handvec.begin(), handvec.end());
	int vecLength = tempVector.size();

	for (int i = 0; i < vecLength - 1; i++) {
		int numOccurences = 0;
		int numCardsRemaining = vecLength;
		for (int j = 0; j < vecLength; j++) {

			if (tempVector[i].Type == tempVector[j].Type)
				numOccurences++;
			if (numOccurences == 2) {
				pairCard = tempVector[i];
				return true;
			}
		}
	}
	return false;
}

Card Poker::EvaluateHighCard() const
{
	std::vector<Card> tempVector = Poker::flopCards;//tempvector to store both hand cards and flop cards in one vector
	std::vector<Card> handvec = Poker::currentPlayer->getHand().getCardVector();
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
