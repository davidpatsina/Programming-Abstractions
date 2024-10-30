/*
 * File: UniversalHealthCoverage.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the UniversalHealthCoverage problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
#include "console.h"
#include "foreach.h"
using namespace std;

/* Function: canOfferUniversalCoverage(Set<string>& cities,
 *                                     Vector< Set<string> >& locations,
 *                                     int numHospitals,
 *                                     Vector< Set<string> >& result);
 * Usage: if (canOfferUniversalCoverage(cities, locations, 4, result)
 * ==================================================================
 * Given a set of cities, a list of what cities various hospitals can
 * cover, and a number of hospitals, returns whether or not it's
 * possible to provide coverage to all cities with the given number of
 * hospitals.  If so, one specific way to do this is handed back in the
 * result parameter.
 */
bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
                               Vector< Set<string> >& result);

bool canOfferUniversalCoverageRec(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
							   Vector< Set<string> >& result,
							   Set<int> chosenLoc);

bool isCoveredCities(Set<string>& cities, Vector< Set<string> >& result);
Set<string> getCoverdCites(Vector< Set<string> >& result);



int main() {
    /* TODO: Add testing code here! */
	Set<string> cities;
	cities.add("A");
	cities.add("B");
	cities.add("C");
	cities.add("D");
	cities.add("E");
	cities.add("F");
	
	Vector< Set<string> > locations;
	Set<string> first;
	first.add("A");
	first.add("B");
	first.add("C");

	Set<string> second;
	second.add("A");
	second.add("C");
	second.add("D");

	Set<string> third;
	third.add("B");
	third.add("F");

	Set<string> fourth;
	fourth.add("C");
	fourth.add("E");
	fourth.add("F");

	locations.add(first);
	locations.add(second);
	locations.add(third);
	locations.add(fourth);

	Vector<Set<string> > result;
	
	int num = 2;

	if (canOfferUniversalCoverage(cities, locations, num, result)){
		for(int i = 0; i < result.size(); i++){
			foreach(string city in result[i]){
				cout<<city<<" ";
			}
			cout<<endl;
		}
	} else cout<<"false"<<endl;

    return 0;
}

Set<string> getCoverdCites(Vector< Set<string> >& result){
	Set<string> coveredCities;
	for (int i = 0; i < result.size(); i++){
		foreach (string city in result[i]){
			if (!coveredCities.contains(city)){
				coveredCities.add(city);
			}
		}
	}

	return coveredCities;
}

bool isCoveredCities(Set<string>& cities, Vector< Set<string> >& result){
	Set<string> coveredCities = getCoverdCites(result);
	if (cities.size() == coveredCities.size()) return true;
	return false;
}

bool canOfferUniversalCoverageRec(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
							   Vector< Set<string> >& result,
							   Set<int> chosenLoc){

	if (result.size() == numHospitals) return isCoveredCities(cities, result);

	for (int i = 0; i < locations.size(); i++){
		if (!chosenLoc.contains(i)){
			result.add(locations[i]);
			chosenLoc.add(i);
			if (canOfferUniversalCoverageRec(cities, locations, numHospitals, result, chosenLoc)) return true;
			result.remove(result.size()-1);
			chosenLoc.remove(i);
		}
	}

	return false;

}

bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
							   Vector< Set<string> >& result){
	Set<int> chosenLoc;
	return canOfferUniversalCoverageRec(cities, locations, numHospitals, result, chosenLoc);
}






