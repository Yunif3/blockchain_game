// BY Yunsoo Kim - 6/22/19
#include "System.h"
#include "Generators.h"
#include <unordered_map>

enum Commands {
	create_wallet, check_wallet, check_creature,
	trade, breed, fight, bet, help
};

void print_commands() {
	cout << "[" << create_wallet << "]" << "Create Wallet" << endl;
	cout << "[" << check_wallet << "]" << "Check Wallet" << endl;
	cout << "[" << check_creature << "]" << "Check Creature" << endl;
	cout << "[" << trade << "]" << "Trade" << endl;
	cout << "[" << breed << "]" << "Breed" << endl;
	cout << "[" << fight << "]" << "Fight" << endl;
	//cout << "[" << bet << "]" << "Bet" << endl;
}
class Game {
private:
	// This will be tracked by the blockchain later
	unordered_map<string, Wallet> wallets;
	unordered_map<string, Creature> creatures;
	unordered_map<string, Currency> currencies;
	System_contract system;
	Creature_generator creature_gen;
	Currency_generator currency_gen;

	bool validate_wallet(string public_key) {
		cout << "Please validate your wallet by entering your private key" << endl;
		string private_key;
		cin >> private_key;
		return wallets[public_key].check_private_key(private_key);
	}

	bool wallet_exists(string pub_key) {
		return wallets.find(pub_key) != wallets.end();
	}

public:
	void create_wallet(string public_key, string private_key) {
		wallets[public_key] = Wallet(private_key, public_key);
		creature_gen.random_gen(100, true, wallets[public_key]);
		creature_gen.random_gen(100, false, wallets[public_key]);
	}
	
	void check_wallet(string public_key) {
		if (wallet_exists(public_key)) {
			wallets[public_key].check_all_creatures();
			cout << "your currency balance is: " << wallets[public_key].get_currency_count() << endl;
		}
	}

	void check_wallet(string public_key, int index) {
		if (wallet_exists(public_key)) {
			wallets[public_key].check_creature(index);
		}
	}
	
	void trade(string pub_key1, string pub_key2) {
		if (!wallet_exists(pub_key1) || !wallet_exists(pub_key2))
			return;

		Wallet &w1 = wallets[pub_key1];
		Wallet &w2 = wallets[pub_key2];

		cout << "Which Creature would you like to trade? " << endl;
		w1.check_all_creatures();
		int give;
		cin >> give;

		cout << "How much currency would you like to use? " << endl;
		int amount;
		cin >> amount;
		if (amount > w1.get_currency_count()) { return; }

		cout << "Which Creature would you like to get? " << endl;
		w2.check_all_creatures();
		int get;
		cin >> get;

		if (validate_wallet(pub_key1) && validate_wallet(pub_key2)) {
			system.trade_creatures(w1, w2, w1.get_creature(give), w2.get_creature(get));
			system.give_currency(w1, w2, amount);
		}
	}

	void breed(string pub_key) {
		if (wallets.find(pub_key) == wallets.end())
			return;

		Wallet &w = wallets[pub_key];
		cout << "Which Creature would you like to breed? " << endl;
		w.check_all_creatures();
		int one;
		cin >> one;

		cout << "Which Creature would you like to breed " << one << " with?" << endl;
		w.check_all_creatures();
		int two;
		cin >> two;

		if (!validate_wallet(pub_key))
			return;
		if (w.get_creature(one).get_sex() != w.get_creature(two).get_sex() &&
			w.get_creature(one).get_type() == w.get_creature(two).get_type())
			return;

		creature_gen.breed(w.get_creature(one), w.get_creature(two), w);
	}

	void fight_monster(string pub_key) {
		if (!wallet_exists(pub_key))
			return;

		Wallet &w = wallets[pub_key];
		cout << "Which Creature would you like to fight with?" << endl;
		w.check_all_creatures();
		int one;
		cin >> one;

		Creature monster = creature_gen.monster_random_gen(w.get_creature(one).get_power());
		if (system.battle(w.get_creature(one), monster)) {
			currency_gen.reward(monster.get_power() / 2, w);
		}
	}
};


int main() {
	Game driver;
	string input;
	string ans1, ans2;
	while (true) {
		cout << "Please enter the number of desired command or type \"help\"" << endl;
		cin >> input;
		if (input == "help") { print_commands(); }
		else if (input == "quit") { break; }

		switch (stoi(input)) {
			case 0: 
				cout << "Please enter the public key of the new wallet" << endl;
				cin >> ans1;
				cout << "Please enter the private key of the new wallet" << endl;
				cin >> ans2;
				driver.create_wallet(ans1, ans2);
				break;
			case 1: 
				cout << "Please enter the public key of the wallet" << endl;
				cin >> ans1;
				driver.check_wallet(ans1);
				break;
			case 2:
				cout << "Please enter the public key of the wallet" << endl;
				cin >> ans1;
				cout << "Please enter the index of the creature" << endl;
				cin >> ans2;
				driver.check_wallet(ans1, stoi(ans2));
				break;
			case 3:
				cout << "Please enter the public key of your wallet" << endl;
				cin >> ans1;
				cout << "Please enter the public key of the other person's wallet" << endl;
				cin >> ans2;
				driver.trade(ans1, ans2);
				break;
			case 4:
				cout << "Please enter the public key of your wallet" << endl;
				cin >> ans1;
				driver.breed(ans1);
				break;
			case 5:
				cout << "Please enter the public key of your wallet" << endl;
				cin >> ans1;
				driver.fight_monster(ans1);
				break;
		}
		cout << "Thank you for playing the game!" << endl;
	}
	return 0;
}