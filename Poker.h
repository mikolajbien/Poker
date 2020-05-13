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
	Poker();
	bool CheckRoyalFlush();
	bool CheckStraightFlush();
	bool CheckFourOfAKind();
	bool CheckFullHouse();
	bool CheckFlush();
	bool CheckStraight();
	bool CheckThreeOfAKind();
	bool CheckTwoPairs();
	bool CheckOnePair();
	Card EvaluateHighCard();

	void DealOutCards();
};