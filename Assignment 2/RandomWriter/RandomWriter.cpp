/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Random Writer problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <fstream>
#include "console.h"
#include "foreach.h"
#include <vector>
#include "foreach.h"
#include "map.h"
#include "random.h"
#include <string>
using namespace std;

int const charsNumber = 2000;

void solution();

void openFile(ifstream& input);
void getMarkovNum(int& markovNumber);

Map<string, Vector<char> > getData(ifstream& input, int markovNum, Vector<string>& cartrige);

void dataOrganise(Vector<string>& cartrige, Map<string, Vector<char>>& data, int markovNum, char ch, int count);
void forLessThanMarkov(Vector<string>& cartrige, char ch);
void forMoreThanMarkov(Vector<string>& cartrige, Map<string, Vector<char>>& data, char ch);
void updateData(Map<string, Vector<char>>& data, string part);

void writeText(Map<string, Vector<char>>& data, Vector<string> cartrige);
string getLastPart(Vector<string> cartrige, Map<string, Vector<char>>& data);
string getFrequentPart(Map<string, Vector<char>>& data);

int main() {
	solution();
    return 0;
}


void solution(){
	ifstream input;	
	Vector<string> cartrige;
	int markovNumber = 0;
	
	openFile(input);
	getMarkovNum(markovNumber);
	
	Map<string, Vector<char>> data = getData(input, markovNumber, cartrige);

	writeText(data, cartrige);
		
}

void openFile(ifstream& input){
	string fileName;
	while(true){
		cout<<"Enter the source text: ";
		getline(cin, fileName);
		input.open(fileName.c_str());
		if (input.is_open()) break;
		cout<<"Unable to open that file. Try again."<<endl;
	}
}

void getMarkovNum(int& markovNumber){
	int result;
	while(true){
		cout<<"Enter the markov order [1-10]: ";
		cin>>result;
		if (result > 0 && result < 11){
			markovNumber = result; 
			break;
		}
		cout<<"That value is out of range."<<endl;
	}
	cout<<"Processing file..."<<endl;
}


Map<string, Vector<char> > getData(ifstream& input, int markovNum, Vector<string>& cartrige){

	char ch;
	Map<string, Vector<char>> data;
	int count = 0;
	
	while (input.get(ch)){
		count++;
		dataOrganise(cartrige, data, markovNum, ch, count);
	}

	input.close();

	return data;
}

void dataOrganise(Vector<string>& cartrige, Map<string, Vector<char>>& data, int markovNum, char ch, int count){
	if (count <= markovNum){
		 forLessThanMarkov(cartrige, ch);
	} else forMoreThanMarkov(cartrige, data, ch);
}

void forLessThanMarkov(Vector<string>& cartrige, char ch){
	string newPart;
	newPart.push_back(ch);
	if (!cartrige.isEmpty()){
		for (int i = 0; i < cartrige.size(); i++){
			cartrige[i].push_back(ch);
		}
	}
	cartrige.add(newPart);
}

void forMoreThanMarkov(Vector<string>& cartrige, Map<string, Vector<char>>& data, char ch){
	string part = cartrige[0];
	part.push_back(ch);
	cartrige.remove(0);
	for (int i = 0; i < cartrige.size(); i++){
		cartrige[i].push_back(ch);
	}
	string newPart;
	newPart.push_back(ch);
	cartrige.add(newPart);

	updateData(data, part);
}


void updateData(Map<string, Vector<char>>& data, string part){
	char ch = part[part.length()-1];
	part = part.substr(0, part.length()-1);
	if (data.containsKey(part)){
		data[part].add(ch);
	} else {
		Vector<char> chars;
		chars.add(ch);
		data.put(part, chars);
	}
}


void writeText(Map<string, Vector<char>>& data, Vector<string> cartrige){
	string endingPart = getLastPart(cartrige, data);
	string currentPart = getFrequentPart(data);	

	int charsInpart = cartrige[0].length()+1;
	int num = charsNumber - currentPart.length();

	for (int i = 0; i < num; i++){
		if (currentPart == endingPart) break;
		int n = randomInteger(0, data[currentPart].size()-1);
		cout<<data[currentPart].get(n);
		currentPart = currentPart.substr(1) + data[currentPart].get(n);
	}
	
}

string getLastPart(Vector<string> cartrige, Map<string, Vector<char>>& data){
	string lastPart = cartrige[0];
	if (data.containsKey(lastPart)) return "";
	return lastPart;
}


string getFrequentPart(Map<string, Vector<char>>& data){
	int count = 0;
	string part;
	foreach(string key in data){
		if (data[key].size() > count){
			count = data[key].size();
			part = key;
		}
	}
	return part;
}
