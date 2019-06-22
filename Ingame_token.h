// BY Yunsoo Kim - 6/22/19
#pragma once
#include "Erc_721.h"
#include "Erc_20.h"
#include <random>
#include <iostream>

enum Type {
	fire, water, grass, air, steel
};

class Creature : public Erc_721 {
friend class Creature_generator;

private:
	string name;
	Type type;
	int power;
	bool sex;

	// TODO there must be a way to keep track of all the floating tokens (i.e blockchain ledger)
	Creature(Type t, int p, bool s)
		:Erc_721(), name("NULL"), type(t), power(p), sex(s) {}

	Creature breed(Creature other) {
		// TODO the power algorithm is certainly destined to change
		int child_power = (power + other.power) * 1.1;
		bool child_sex = rand() % 2;

		// TODO there must be a way to keep track of all the floating tokens (i.e blockchain ledger)
		return Creature(type, child_power, child_sex);
	}

public:
	// getter functions
	string get_name() {
		return name;
	}
	Type get_type() {
		return type;
	}
	int get_power() {
		return power;
	}
	int get_sex() {
		return int(sex);
	}
	void print_creature() {
		cout << "-----------------------" << endl;
		cout << "Creature Info:" << endl;
		cout << "Name: " << name << endl;
		cout << "Type: " << type << endl;
		cout << "Power: " << power << endl;
		cout << "Sex: " << int(sex) << endl;
	}

	// manipulation functions
	void change_name(string alt) {
		name = alt;
	}
	
};

class Currency : public Erc_20 {
private:
	friend class Currency_generator;
	// TODO there must be a way to keep track of all the floating tokens (i.e blockchain ledger)
	Currency ()
		:Erc_20() {}
public:
};