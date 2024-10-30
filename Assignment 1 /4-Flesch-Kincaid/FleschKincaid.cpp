/*
 * File: FleschKincaid.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Flesch-Kincaid problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <fstream>
#include <string>
#include "tokenscanner.h"
#include "vector.h"
#include <cctype>
#include "console.h"

using namespace std;

const double c0 = -15.59;
const double c1 = 0.39;
const double c2 = 11.8;

struct textInformation{
	int words;
	int sentences;
	int syllables;
};

void solution();

textInformation getTexInfo();
void writeGrade(textInformation txtinf);

void setInfo(TokenScanner& scanner, int& words, int& sentences, int& syllables);
int syllablesCounterInTheWord(string word);
bool isVowel(char ch);

void textInformationCheaker(int& words, int& sentences);
void saveInfo(int words, int sentences, int syllables, textInformation& txtinf);

double gradeCalculate(int words, int sentences, int syllables);

int main() {


	solution();

    return 0;
}


void solution(){	
	textInformation txtinf = getTexInfo();
	writeGrade(txtinf);
}

textInformation getTexInfo(){
	ifstream inputFile;
	while (true){
		string fileName;
		cout<<"Enter file name:"<<endl;
		cin>>fileName;
		inputFile.open(fileName.c_str());
		if (!inputFile.is_open()){
			cout<<"There isn't file with name "<<fileName<<endl;
			continue;
		} else break;
	}

	TokenScanner scanner;
	scanner.setInput(inputFile);

	textInformation txtinf;
	
	int words = 0;
	int sentences = 0;
	int syllables = 0;

	setInfo(scanner, words, sentences, syllables);

	textInformationCheaker(words, sentences);

	saveInfo(words, sentences, syllables, txtinf);
	
	return txtinf;
}

void setInfo(TokenScanner& scanner, int& words, int& sentences, int& syllables){
	scanner.ignoreWhitespace();
	scanner.addWordCharacters("'");


	while (scanner.hasMoreTokens()){
		string word = scanner.nextToken();
		if (isalpha(word[0])){
			words++;
			syllables = syllables + syllablesCounterInTheWord(word);
		} else if (word[0]=='.' || word[0]=='!' || word[0]=='?' ){
			sentences++;
		}
	}
}


void saveInfo(int words, int sentences, int syllables, textInformation& txtinf){
	txtinf.sentences = sentences;
	txtinf.syllables = syllables;
	txtinf.words = words;
		
}

void textInformationCheaker(int& words, int& sentences){
	if (words == 0) words = 1;
	if (sentences == 0) sentences = 1;
}

void writeGrade(textInformation txtinf){
	int words = txtinf.words;
	int sentences = txtinf.sentences;
	int syllables = txtinf.syllables;
	cout<<"Number of words is: "<<words<<endl;
	cout<<"Number of sentences is: "<<sentences<<endl;
	cout<<"Number of syllables is: "<<syllables<<endl;
	cout<<"Grade of the text is: "<<gradeCalculate(words, sentences, syllables)<<endl;
}


bool isVowel(char ch){
	if (ch== 'a'|| ch== 'e'|| ch== 'i'|| ch== 'o'|| ch== 'u' || ch== 'y'||
		ch== 'A'|| ch== 'E'|| ch== 'I'|| ch== 'O'|| ch== 'U' || ch== 'Y'){	
		return true;
	}
	return false;
}

int syllablesCounterInTheWord(string word){
	int syllables = 0;
	
	int syllablesCombo = 0;

	for (int i =0; i < word.length(); i++){
		if (isVowel(word[i])){
			if(syllablesCombo == 0){
			syllables++;
			syllablesCombo++;
			} else syllablesCombo++;
		} else syllablesCombo = 0;
	}

	if (word.length() > 2 && word[word.length()-1] == 'e'){
		if(syllables>1){
			syllables--;
		}
	}
	return syllables;
}




double gradeCalculate(int words, int sentences, int syllables){
	return c0 + c1*((words+0.0)/(sentences+0.0))+c2*((syllables+0.0)/(words+0.0));
}


