#pragma once
#include "Hand.h"
#include "Deck.h"

class Player {
private:
	std::string name;
	Hand playerHand;
	
	bool isFolded;
	//bool isSittingOut = false;
	double Money;
public:
	Player();
	Player(std::string name);
	void DealToPlayer(Deck &gameDeck);
	void PlaceBet(const double betAmount);
	bool GetIsSittingOut() const;
	bool GetIsFolded() const;
	Hand getHand() const;
	std::string getName() const;
	
};