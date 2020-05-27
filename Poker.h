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
	bool operator<(Ranking r) const {//for sorting and breaking ties
		if (this->rankOfHand < r.rankOfHand)
			return true;
		else if (this->rankOfHand > r.rankOfHand)
			return false;
		else {
			switch (rankOfHand) {
			case HAND_RANKING::HIGH_CARD:
				if (this->tiebreakerCards[0] > r.tiebreakerCards[0]) {
					return false;
				}
				else if (this->tiebreakerCards[0] < r.tiebreakerCards[0])
					return true;
				else {
					if (this->tiebreakerCards[1] > r.tiebreakerCards[1]) {
						return false;
					}
					else if (this->tiebreakerCards[1] < r.tiebreakerCards[1]) {
						return true;
					}
					else {
						if (this->tiebreakerCards[2] > r.tiebreakerCards[2]) {
							return false;
						}
						else if (this->tiebreakerCards[2] < r.tiebreakerCards[2]) {
							return true;
						}
						else {
							if (this->tiebreakerCards[3] > r.tiebreakerCards[3]) {
								return false;
							}
							else if (this->tiebreakerCards[3] < r.tiebreakerCards[3]) {
								return true;
							}
							else {
								if (this->tiebreakerCards[4] > r.tiebreakerCards[4]) {
									return false;
								}
								else if (this->tiebreakerCards[4] < r.tiebreakerCards[4]) {
									return true;
								}
								else//hands are equal!
									return false;
							}
						}
					}
				}
				break;
			case HAND_RANKING::ONE_PAIR:
				if (this->tiebreakerCards[0] > r.tiebreakerCards[0]) {//pair
					return false;
				}
				else if (this->tiebreakerCards[0] < r.tiebreakerCards[0])//pair
					return true;
				else {
					if (this->tiebreakerCards[1] > r.tiebreakerCards[1]) {//kicker
						return false;
					}
					else if (this->tiebreakerCards[1] < r.tiebreakerCards[1]) {//kicker
						return true;
					}
					else {
						if (this->tiebreakerCards[2] > r.tiebreakerCards[2]) {//second kicker
							return false;
						}
						else if (this->tiebreakerCards[2] < r.tiebreakerCards[2]) {//second kicker
							return true;
						}
						else {
							if (this->tiebreakerCards[3] > r.tiebreakerCards[3]) {//second kicker
								return false;
							}
							else if (this->tiebreakerCards[3] < r.tiebreakerCards[3]) {//second kicker
								return true;
							}
							else
								return false; //hands are equal!
						}
					}
				}
				break;


			case HAND_RANKING::TWO_PAIR:
				if (this->tiebreakerCards[0] > r.tiebreakerCards[0]) {//pair
					return false;
				}
				else if (this->tiebreakerCards[0] < r.tiebreakerCards[0])//pair
					return true;
				else {
					if (this->tiebreakerCards[1] > r.tiebreakerCards[1]) {//kicker
						return false;
					}
					else if (this->tiebreakerCards[1] < r.tiebreakerCards[1]) {//kicker
						return true;
					}
				}
			case HAND_RANKING::THREE_OF_A_KIND:
				if (this->tiebreakerCards[0] > r.tiebreakerCards[0]) {//triplet
					return false;
				}
				else if (this->tiebreakerCards[0] < r.tiebreakerCards[0])//triplet
					return true;
				else {
					if (this->tiebreakerCards[1] > r.tiebreakerCards[1]) {//kicker 1 
						return false;
					}
					else if (this->tiebreakerCards[1] < r.tiebreakerCards[1]) {//kicker 1 
						return true;
					}
					else {
						if (this->tiebreakerCards[2] > r.tiebreakerCards[2]) {//kicker 2 
							return false;
						}
						else if (this->tiebreakerCards[2] < r.tiebreakerCards[2]) {//kicker 2
							return true;
						}
						else//hands are equal!
							return false;
					}
				}
				break;

			case HAND_RANKING::STRAIGHT:
				if (this->tiebreakerCards[0] > r.tiebreakerCards[0]) {//straight high card
					return false;
				}
				else if (this->tiebreakerCards[0] < r.tiebreakerCards[0])//straight high card
					return true;
				else
					return false; // equal hands
				break;
			case HAND_RANKING::FLUSH:
				if (this->tiebreakerCards[0] > r.tiebreakerCards[0]) {//flush high card
					return false;
				}
				else if (this->tiebreakerCards[0] < r.tiebreakerCards[0])//flush high card
					return true;
				else
					return false;//equal flushes
				break;
			case HAND_RANKING::FULL_HOUSE:
				if (this->tiebreakerCards[0] > r.tiebreakerCards[0]) {//triplet
					return false;
				}
				else if (this->tiebreakerCards[0] < r.tiebreakerCards[0])//triplet
					return true;
				else {
					if (this->tiebreakerCards[1] > r.tiebreakerCards[1]) {//pair
						return false;
					}
					else if (this->tiebreakerCards[1] < r.tiebreakerCards[1]) {//pair
						return true;
					}
					else
						return false;//equal full houses
				}
			case HAND_RANKING::FOUR_OF_A_KIND:
				if (this->tiebreakerCards[0] > r.tiebreakerCards[0]) {//triplet
					return false;
				}
				else if (this->tiebreakerCards[0] < r.tiebreakerCards[0])//triplet
					return true;
				else
					return false;
				break;

			case HAND_RANKING::STRAIGHT_FLUSH:
				if (this->tiebreakerCards[0] > r.tiebreakerCards[0]) {//flush high card
					return false;
				}
				else if (this->tiebreakerCards[0] < r.tiebreakerCards[0])//flush high card
					return true;
				else
					return false;
				break;
			case HAND_RANKING::ROYAL_FLUSH:
				return false;


			default:
				return false;
			}
		}
	}
		

};											
class Poker {//class representing a Poker Game
private:
	Player* currentPlayer;
	Player* Dealer;
	Player* bigBlind;
	Player* smallBlind;
	int round;
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
	
	Poker(double bigBlindAmt, double smallBlindAmt);
	Poker(int amountOfFlopCards, int numPlayers);//TESTING
	void ChooseRandomDealer();
	void BetBlinds();


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

	void AddPlayer(Player p);
	void DealOutCards();
	HAND_RANKING EvaluateCurrentPlayerHand();
	std::vector<Player*> DetermineWinner();
	
	
};