#pragma once
#include "stdafx.h"
#include "Player.h"
#include "Deck.h"
enum class HAND_RANKING { HIGH_CARD, ONE_PAIR, TWO_PAIR, THREE_OF_A_KIND, STRAIGHT, FLUSH, FULL_HOUSE, FOUR_OF_A_KIND, STRAIGHT_FLUSH, ROYAL_FLUSH };

struct Ranking {
	Player* Owner;
	HAND_RANKING rankOfHand;
	std::vector<TYPE_CARD> tiebreakerCards;//[0]=straight, flush, straightflush,1stpair of two pair, one pair card, triplet card of full house, three of a kind card, high card
											//[1]= pair in full house, lower pair in two pair, high card in one pair
											//[2], high card in two pair
											//[3], extra
											//[4]extra
	Ranking(Player* playerPtr) {
		Owner = playerPtr;
		rankOfHand = HAND_RANKING::HIGH_CARD;
	}
	bool operator<(Ranking r) const {//for sorting
		if (this->rankOfHand < r.rankOfHand) {
			return true;
		}
		return false;
	}

};											
class Poker {//class representing a Poker Game
private:
	Player currentPlayer;
	
	double bigBlindAmt;
	double smlBlindAmt;
	double highestBet;
	int numPlayers;
	std::vector<Player> Players;
	std::vector<Card> flopCards;
	std::vector<Ranking> handRankings;
	Deck gameDeck;
	void removeCards(TYPE_CARD type, std::vector<Card> &cardVec) const;
	std::vector<Card> combineHandAndFlopCards() const;
public:
	

	Poker(int amountOfFlopCards, int numPlayers);
	bool CheckRoyalFlush() const;
	bool CheckStraightFlush(std::vector<Card> &straightflushCards, Card& highCard) const;
	bool CheckFourOfAKind() const;
	bool CheckFullHouse(Card &tripletCard, Card &pairCard) const;
	bool CheckFlush(std::vector<Card> &flushCards) const;
	bool CheckStraight(std::vector<Card> &straightCards) const;
	bool CheckThreeOfAKind(Card &threeOfAKindCard) const;
	bool CheckTwoPairs(Card &higherPairCard,Card &lowerPairCard) const;
	bool CheckOnePair(Card &pairCard) const;
	Card EvaluateHighCard() const; 
	static Card EvaluateHighCard(std::vector<Card> cardVec);

	void DealOutCards();
	HAND_RANKING EvaluateCurrentPlayerHand();
	Player* DetermineWinner();

};