// BY Yunsoo Kim - 6/22/19
#pragma once
#include <string>

class Erc_20 {
private:
	// for now, the hash is incremented by one every time
	static int counter;

protected:
	Erc_20() {
		counter++;
	}

	string owner_pub;

public:
	int get_counter() {
		return counter;
	}

	bool transfer(string receiver_pub) {
		owner_pub = receiver_pub;
		return true;
	}

	string get_owner() {
		return owner_pub;
	}
};