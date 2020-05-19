#pragma once
#include "stdafx.h"
#include "Player.h"
#include "Deck.h"
enum class HAND_RANKING { HIGH_CARD, ONE_PAIR, TWO_PAIR, THREE_OF_A_KIND, STRAIGHT, FLUSH, FULL_HOUSE, FOUR_OF_A_KIND, STRAIGHT_FLUSH, ROYAL_FLUSH };

struct Ranking {
	Player Owner;
	HAND_RANKING Ranking;

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
	Deck gameDeck;
	void removeCards(TYPE_CARD type, std::vector<Card> &cardVec) const;
public:
	Poker(Player player, Deck deck, int amountOfFlopCards);

	Poker(int amountOfFlopCards, int numPlayers);
	bool CheckRoyalFlush() const;
	bool CheckStraightFlush(std::vector<Card> &straightflushCards) const;
	bool CheckFourOfAKind() const;
	bool CheckFullHouse(Card &tripletCard, Card &pairCard) const;
	bool CheckFlush(std::vector<Card> &flushCards) const;
	bool CheckStraight(std::vector<Card> &straightCards) const;
	bool CheckThreeOfAKind(Card &threeOfAKindCard) const;
	bool CheckTwoPairs(Card &higherPairCard,Card &lowerPairCard) const;
	bool CheckOnePair() const;
	Card EvaluateHighCard();
	static Card EvaluateHighCard(std::vector<Card> cardVec);

	void DealOutCards();

	HAND_RANKING EvaluateCurrentPlayerHand();

};