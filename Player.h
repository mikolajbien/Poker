#pragma once
#include "Hand.h"
#include "Deck.h"
enum PLAYER_STATUS{BIG_BLIND, SMALL_BLIND, DEALER, NO_STATUS};
class Player {
private:
	Hand playerHand;
	PLAYER_STATUS Status;
	bool isFolded = false;
	bool isSittingOut = false;
	int Money = 0;
public:
	
	void DealToPlayer(Deck &gameDeck);
	void PlaceBet(const int betAmount);
	const bool GetIsSittingOut();
	const bool GetIsFolded();
	Hand getHand() const;
};