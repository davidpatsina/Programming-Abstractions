/*
 * File: NumericConversions.cpp
 * ---------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Numeric Conversions problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
using namespace std;

/* Function prototypes */

string intToString(int n);
int stringToInt(string str);
bool checker(string number);

/* Main program */

int main() {
    // [TODO: fill in the code]
	int n;
	cout<<"Enter int number: "<<endl;
	cin>>n;
	cout<<"Your number in strnig: "<<intToString(n)<<endl;

	while (true){
	string number;
	cout<<"Enter string number number: "<<endl;
	cin>>number;
	
	if (!checker(number)){
		cout<<"It contains a letter!"<<endl;
		cout<<"Try it again!"<<endl<<endl;
		continue;
	}

	cout<<"Your number in int: "<<stringToInt(number)<<endl;
	break;
	}
    return 0;
}

bool checker(string number){
	for (int i=0; i<number.length(); i++){

		if (number[i] > '9' || number[i] < '0'){
			if (i ==0 && number[0] == '-') continue;
			return false;
		}

	}
	return true;
}

int stringToInt(string str){
	if (str[0] == '-'){
		return (-1)*stringToInt(str.substr(1));
	}

	int lastDig = str[str.length()-1]-'0';

	if (str.length() == 1){
		return lastDig;
	}
	
	string numWithoutLastDigit = str.substr(0, str.length()-1);

	return 10*stringToInt(numWithoutLastDigit)+lastDig;
}

string intToString(int n){
	if (n < 0){
		return "-"+intToString(-n);
	} 
	
	if (n < 10){
		string ss = "";
		return ss+(char(n + '0'));
	}

	int firsPartOfNum = n/10;
	int secondPartOfNum = n%10;
	return 	intToString(n/10) + intToString(n%10);
}
