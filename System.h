// BY Yunsoo Kim - 6/22/19
#pragma once
#include "Wallet.h"

class System_contract {
public:
	// These are examples of smart contracts that can be made with given functions
	void trade_creatures(Wallet w1, Wallet w2, Creature c1, Creature c2) {
		w1.transfer_creature(c1, w2);
		w2.transfer_creature(c2, w1);
	}

	void sell_creature(Wallet w1, Wallet w2, Creature c1, int money) {
		w1.transfer_creature(c1, w2);
		for (int i = 0; i < money; ++i) {
			w2.transfer_currency(w1);
		}
	}

	bool battle(Creature c1, Creature c2) {
		// TODO this exact algorithm is subject to change.
		int c1_wins = 0;
		for (int i = 0; i < 7; ++i) {
			if (rand() % c1.get_power() > rand() % c2.get_power()) {
				c1_wins++;
			}
		}
		return c1_wins > 3;
	}

	void give_currency(Wallet w1, Wallet w2, int amount) {
		if (w1.get_currency_count() < amount)
			return;
		for (int i = 0; i < amount; ++i) {
			w1.transfer_currency(w2);
		}
	}

	void bet(Wallet w1, Wallet w2, int amount, bool result) {
		if (w1.get_currency_count() < amount || w2.get_currency_count() < amount)
			return;
		if (result) {
			give_currency(w1, w2, amount);
		}
		else {
			give_currency(w2, w1, amount);
		}
	}
};