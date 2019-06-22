// BY Yunsoo Kim - 6/22/19
#pragma once
#include <string>
#include <vector>
#include "Ingame_token.h"

using namespace std;

class Wallet {
private:
	string private_key;
	string public_key;
	vector<Creature> creatures;
	vector<Currency> currencies;

	int get_creature_index(Creature c) {
		for (int i = 0; i < int(creatures.size()); ++i) {
			if (creatures[i].get_unique_hash() == c.get_unique_hash()) {
				return i;
			}
		}
	}
	
public:
	Wallet(string priv, string pub)
		:private_key(priv), public_key(pub) {}

	string get_pub_key() {
		return public_key;
	}
	int get_creature_count() {
		return creatures.size();
	}
	int get_currency_count() {
		return currencies.size();
	}
	Creature get_creature(int index) {
		return creatures[index];
	}

	bool check_private_key(string key) {
		return private_key == key;
	}

	void check_all_creatures() {
		cout << "Checking all Owned Creatures" << endl;
		for (int i = 0; i < int(creatures.size()); ++i) {
			creatures[i].print_creature();
			cout << "Current index = " << i << endl;
		}
	}
	void check_creature(int index) {
		cout << "Checking a Creature" << endl;
		get_creature(index).print_creature();
	}
	

	void receive(Creature c) {
		c.transfer(public_key);
		creatures.push_back(c);
	}
	void receive(Currency c) {
		c.transfer(public_key);
		currencies.push_back(c);
	}
	void transfer_creature(Creature c, Wallet w) {
		w.receive(c);
		creatures.erase(creatures.begin() + get_creature_index(c));
	}
	void transfer_currency(Wallet w) {
		w.receive(currencies.back());
		currencies.pop_back();
	}
};