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
public:
	Poker(Player player, Deck deck, int amountOfFlopCards);
	bool CheckRoyalFlush();
	bool CheckStraightFlush();
	bool CheckFourOfAKind();
	bool CheckFullHouse();
	bool CheckFlush(std::vector<Card> &flushCards);
	bool CheckStraight(std::vector<Card> &straightCards);
	bool CheckThreeOfAKind();
	bool CheckTwoPairs();
	bool CheckOnePair();
	Card EvaluateHighCard();

	void DealOutCards();
};