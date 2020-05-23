#include "stdafx.h"
#include "Player.h"


Player::Player()
{
}

Player::Player(std::string name)
{
	this->name = name;
	this->Status = PLAYER_STATUS::NO_STATUS;
}

void Player::DealToPlayer(Deck &gameDeck)
{
	Player::playerHand.addCards(gameDeck.Deal(), gameDeck.Deal());
}

const bool Player::GetIsSittingOut()
{
	return Player::isSittingOut;
}

const bool Player::GetIsFolded()
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
