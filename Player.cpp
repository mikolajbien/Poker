#include "stdafx.h"
#include "Player.h"
#include "stdafx.h"
#include "Player.h"

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
