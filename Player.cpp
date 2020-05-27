#include "stdafx.h"
#include "Player.h"


Player::Player()
{
}

Player::Player(std::string name)
{
	this->isFolded = false;
	this->name = name;
	
}

void Player::DealToPlayer(Deck &gameDeck)
{
	Player::playerHand.addCards(gameDeck.Deal(), gameDeck.Deal());
}

void Player::PlaceBet(const double betAmount)
{
	this->Money -= betAmount;
}



bool Player::GetIsFolded() const
{
	return Player::isFolded;
}

Hand Player::getHand() const
{
	return Player::playerHand;
}

std::string Player::getName() const
{
	return this->name;
}


