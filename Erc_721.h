// BY Yunsoo Kim - 6/22/19
#pragma once
#include <string>

using namespace std;

class Erc_721 {
private:
	// for now, the hash is incremented by one every time
	static int counter;
	int unique_hash;

protected:
	Erc_721() {
		unique_hash = counter;
		++counter;
	}

	string owner_pub;
	
public:
	bool transfer(string receiver_pub) {
		owner_pub = receiver_pub;
		return true;
	}

	string get_owner() {
		return owner_pub;
	}

	int get_unique_hash() {
		return unique_hash;
	}
};