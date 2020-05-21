#pragma once
#include "Hand.h"
#include "Deck.h"
enum class PLAYER_STATUS{BIG_BLIND, SMALL_BLIND, DEALER, NO_STATUS};
class Player {
private:
	std::string name;
	Hand playerHand;
	PLAYER_STATUS Status;
	bool isFolded = false;
	bool isSittingOut = false;
	int Money = 0;
public:
	Player();
	Player(std::string name);
	void DealToPlayer(Deck &gameDeck);
	void PlaceBet(const int betAmount);
	const bool GetIsSittingOut();
	const bool GetIsFolded();
	Hand getHand() const;
	std::string getName() const;
};