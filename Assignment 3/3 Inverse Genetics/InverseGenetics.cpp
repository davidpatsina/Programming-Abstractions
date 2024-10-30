/*
 * File: InverseGenetics.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Inverse Genetics problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include <fstream>
#include "set.h"
#include "map.h"
#include <vector>
#include "foreach.h"
#include "console.h"

using namespace std;

/* Function: listAllRNAStrandsFor(string protein,
 *                                Map<char, Set<string> >& codons);
 * Usage: listAllRNAStrandsFor("PARTY", codons);
 * ==================================================================
 * Given a protein and a map from amino acid codes to the codons for
 * that code, lists all possible RNA strands that could generate
 * that protein
 */
void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons);

/* Function: loadCodonMap();
 * Usage: Map<char, Lexicon> codonMap = loadCodonMap();
 * ==================================================================
 * Loads the codon mapping table from a file.
 */
Map<char, Set<string> > loadCodonMap();
void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons);
Vector<string> combinationsOfProtein(string protein, Map<char, Set<string> >& codons);
void combinationsOfProteinRec(string protein, Map<char, Set<string> >& codons, Vector<string>& names);


int main() {
    /* Load the codon map. */
    Map<char, Set<string> > codons = loadCodonMap();
	string protein;
	cout<<"Enter name of protein: "<<endl;
	cin>>protein;
	listAllRNAStrandsFor(protein, codons);
    /* [TODO: Implement this!] */
    return 0;
}

/* You do not need to change this function. */
Map<char, Set<string> > loadCodonMap() {
    ifstream input("codons.txt");
    Map<char, Set<string> > result;

    /* The current codon / protein combination. */
    string codon;
    char protein;

    /* Continuously pull data from the file until all data has been
     * read.
     */
    while (input >> codon >> protein) {
        result[protein] += codon;
    }

    return result;
}
void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons){
	Vector<string> result = combinationsOfProtein(protein, codons);
	for (int i =0; i < result.size(); i++){
		cout<<result[i]<<endl;
	}
}

Vector<string> combinationsOfProtein(string protein, Map<char, Set<string> >& codons){
	Vector<string> result;
	string emptyString = "";
	result.add(emptyString);
	combinationsOfProteinRec(protein, codons, result);
	return result;
}

void combinationsOfProteinRec(string protein, Map<char, Set<string> >& codons, Vector<string>& names){
	
	if (protein.length()==0) return;
	

	Vector<string> copyOfNames = names;
	names.clear();

	char aminoAcid = protein[0];
	protein = protein.substr(1);
	Set<string> currSet = codons[aminoAcid];


	foreach(string codon in currSet){
		names += copyOfNames;
		for (int i =(names.size()-copyOfNames.size()); i < names.size(); i++){
			names[i] += codon; 
		}
	}

	combinationsOfProteinRec(protein, codons, names);
}


