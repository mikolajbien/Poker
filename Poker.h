#pragma once
#include "stdafx.h"
#include "Player.h"
#include "Deck.h"
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
	bool CheckRoyalFlush() const;
	bool CheckStraightFlush() const;
	bool CheckFourOfAKind() const;
	bool CheckFullHouse(Card &tripletCard, Card &pairCard) const;
	bool CheckFlush(std::vector<Card> &flushCards) const;
	bool CheckStraight(std::vector<Card> &straightCards) const;
	bool CheckThreeOfAKind(Card &threeOfAKindCard) const;
	bool CheckTwoPairs() const;
	bool CheckOnePair() const;
	Card EvaluateHighCard();

	void DealOutCards();
};