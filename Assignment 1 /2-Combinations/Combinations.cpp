/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Combinations problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
using namespace std;

int combination(int n, int m){

	if (n == m || m == 0){
		return 1;
	} 

	return combination(n-1, m)+combination(n-1, m-1);
}


void getCombinations(){
	int n, m;
	while (true){
		cout<<"Enter a total number of items to choose from:"<<endl;
		cin>>n;

		if (n < 0){
			cout<<"The number must be nonnegative!"<<endl;
			continue;
		}

		cout<<"Enter number of items we want to select:"<<endl;
		cin>>m;

		if (m > n){
			cout<<"The number is higer than the total number of items to choose from!"<<endl;
			continue;	
		} else if (m < 0){
			cout<<"The number must be nonnegative!"<<endl;
			continue;
		}
		
		cout<<"The number of combinations is "<<combination(n,m)<<"."<<endl;
		break;
	}
}


int main() {
    // [TODO: fill in the code]
	getCombinations();
    return 0;
}
