// TSP Tester.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include <math.h>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include "./../Austins Helper Class/Helper.h"

using namespace std;

class path {
private:
	vector<Coordinate> pathVal;
	string name = "";
	void setNameBasedOnPath(vector<Coordinate> pathVal) {
		for (int i = 0; i < pathVal.size(); i++) {
			name += pathVal.at(i).getName();
		}
	}

	double getFirstDistance(Coordinate c1, Coordinate c2) {
		double d = sqrt(pow((c2.getX() - c1.getX()), 2) + pow((c2.getY() - c1.getY()), 2));
		return d;
	}

	//Will probably only use this one and just preset distance to 0.0 for the first;
	double getDistance(double distance, Coordinate start, Coordinate c2) {
		double d = sqrt(pow((c2.getX() - start.getX()), 2) + pow((c2.getY() - start.getY()), 2));
		d = d + distance;
		return d;
	}

public:
	path(vector<Coordinate> v) {
		pathVal = v;
		setNameBasedOnPath(pathVal);
	}

	double getPathLength() {
		double pathLength = 0.0;
		pathLength = getDistance(pathLength, pathVal.at(0), pathVal.at(1));
		for (int i = 2; i < pathVal.size(); i++) {
			pathLength = getDistance(pathLength, pathVal.at(i - 1), pathVal.at(i));
		}
		pathLength = getDistance(pathLength, pathVal.at(pathVal.size() - 1), pathVal.at(0));
		return pathLength;
	}

	string getName() {
		return name;
	}
	//get length

};



void grabLetter(vector<Coordinate>, vector<Coordinate>, int);
void lastTwo(vector<Coordinate>, vector<Coordinate>);
vector<Coordinate> availCoor;	//Will define later when we know how many coordinates.

void displayVecCoord(vector<Coordinate>);
//Not sure if I use these
/*
vector<char> startingLetters;
vector<char>& allLetters = startingLetters;
*/
vector<Coordinate> currentPath = {};
vector<Coordinate> bestPath = {};

vector<path> allPaths = {};
double bestDistance = numeric_limits<double>::max();



int main()
{
	srand(time(NULL));

	// TODO Auto-generated method stub

	//File was lost after changing computers. Rebuilt in CPP. 


	//Get input type
		//1. Read from file
		//Do file handling (reading)

		//2. Use Random inputs
		//Do file handling (creating directories)

		//3. Type by hand.

	//Run test
		// determine length - variable
		// assign to avail letters. - not a function - as we only do this once
		// for starting letters
			//currentPath.pushback starting letters
	
	for (int i = 0; i < 5; i++) {
		char c = 'A';
		c += i;
		///int x = rand
		string s(1, c);
		int randomNumber1 = (rand() % 100) + 1;
		int randomNumber2 = (rand() % 100) + 1;
		Coordinate CO = Coordinate(s, randomNumber1, randomNumber2);
		availCoor.push_back(CO);
		cout << availCoor.at(i).getName() << endl;
	}


	//availCoor = { 'A','B','C','D','E'};

	grabLetter(availCoor, currentPath,0);

	std::cout << "Starting to display: " << endl;
	std::cout << "All paths.size() = " << allPaths.size() << endl;
	for (int i = 0; i < allPaths.size(); i++) {
		
			std::cout << allPaths.at(i).getName() << " : ";
			std::cout << allPaths.at(i).getPathLength();
		
		std::cout << endl;
	}
}


void grabLetter(vector<Coordinate> AvailLettParamVal, vector<Coordinate> currentPathParamVal, int depthCounter) {
	std::cout << "GrabLetterCalled." << std::endl;
	depthCounter++;
	std::cout << depthCounter << endl;

	cout << "Avail Lett ParamVal = ";
	displayVecCoord(AvailLettParamVal);
	cout << "Current Path = ";
	displayVecCoord(currentPath);


	int totalAvailLetters = 0;

	//we are going through all letters to see how many are available.
	//I'm going to debug by removing the "totalAvailLetters" condition
	for (int i = 0; i < AvailLettParamVal.size(); i++) {
		
		if (AvailLettParamVal.at(i).getName() != "x") {
			totalAvailLetters++;
		}
	}
	if (totalAvailLetters == 2) {
		string temp = "";

		//I think this is just for debugging
		for (int i = 0; i < currentPathParamVal.size(); i++) {
			//temp += currentPathParamVal.at(i);
		}

		cout << "Temp before Last Two call is: " << temp <<endl;
		lastTwo(AvailLettParamVal, currentPathParamVal);
	}

	for (int i = 0; i < AvailLettParamVal.size(); i++) {
		if (AvailLettParamVal.at(i).getName() == "x") {
			continue;
		}

		
		Coordinate c = AvailLettParamVal.at(i);
		currentPathParamVal.push_back(c);
		AvailLettParamVal.at(i).setName("x");
		grabLetter(AvailLettParamVal, currentPathParamVal, depthCounter);
		currentPathParamVal.pop_back();
		AvailLettParamVal.at(i) = c;

	}
}


void lastTwo(vector<Coordinate> AvailLettParamVal, vector<Coordinate> currentPathParamVal) {
	int first = -27;
	int second = -27;

	//Find last two letters
	for (int i = 0; i < AvailLettParamVal.size(); i++) {
		if (AvailLettParamVal.at(i).getName() != "x") {
			if (first == -27) {
				first = i;
			}
			else {
				second = i;
				break;
			}
		}
		else {
			

		}
	}

	vector<Coordinate> One(currentPathParamVal.begin(), currentPathParamVal.end());
	vector<Coordinate> Two(currentPathParamVal.begin(), currentPathParamVal.end());
	//string Two = "";
	One.push_back( AvailLettParamVal.at(first) );
	One.push_back(AvailLettParamVal.at(second));

	Two.push_back(AvailLettParamVal.at(second));
	Two.push_back(AvailLettParamVal.at(first));

	path onePath = path(One);
	path twoPath = path(Two);

	allPaths.push_back(onePath);
	allPaths.push_back(twoPath);
}

void displayPath(vector<char> v) {
	for (int i = 0; i < v.size(); i++) {
		cout << v.at(i);
	}
	cout << endl;
}

void displayVecCoord(vector<Coordinate> v) {
	for (int i = 0; i < v.size(); i++) {
		cout << v.at(i).getName();
	}
	cout << endl;
}