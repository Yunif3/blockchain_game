// BY Yunsoo Kim - 6/22/19
#pragma once
#include "Ingame_token.h"
#include "Wallet.h"

class Creature_generator {
public:
	void random_gen(int power_limit, Wallet w) {
		int random_power = rand() % power_limit;
		Type random_type = Type(rand() % steel);
		bool random_sex = rand() % 2;
		w.receive(Creature(random_type, random_power, random_sex));
	}
	Creature random_gen(int power_limit, bool sex, Wallet w) {
		int random_power = rand() % power_limit;
		Type random_type = Type(rand() % steel);
		w.receive(Creature(random_type, random_power, sex));
	}
	Creature monster_random_gen(int power_limit) {
		int random_power = rand() % power_limit;
		Type random_type = Type(rand() % steel);
		bool random_sex = rand() % 2;
		return Creature(random_type, random_power, random_sex);
	}

	Creature breed(Creature one, Creature two, Wallet w) {
		w.receive(one.breed(two));
	}
};

class Currency_generator {
public:
	void reward(int n, Wallet w) {
		for (int i = 0; i < n; ++i) {
			w.receive(Currency());
		}
	}
};