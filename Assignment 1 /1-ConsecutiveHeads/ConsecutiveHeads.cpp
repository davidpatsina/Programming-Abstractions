/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Consecutive Heads problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "random.h"

using namespace std;

void coinSimulation(int &counterForFlips){
	bool coin = false;
	int counterForHeads =0;

	while(counterForHeads<3){
		counterForFlips++;
		coin = randomChance(0.5);

		if (coin){
			counterForHeads++;
			cout<<"heads"<<endl;
		} else {
			counterForHeads=0;
			cout<<"tails"<<endl;
		}
	}
}

int main() {
    // [TODO: fill in the code]

	int	counterForFlips =0;

	coinSimulation(counterForFlips);

	cout<<"It took "<<counterForFlips<<" to get 3 consecutive heads."<<endl;

    return 0;
}
