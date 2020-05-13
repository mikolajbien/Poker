#include "stdafx.h"
#include "Poker.h"

void Poker::DealOutCards()
{
	for (Player p : Players) {
		if (!p.GetIsSittingOut()) {
			p.DealToPlayer(Poker::gameDeck);
		}
	}
}
