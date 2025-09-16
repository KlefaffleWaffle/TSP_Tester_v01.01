

#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include <math.h>
#include <cstdlib> 
#include <ctime>   
#include <algorithm>
#include "./../Austins Helper Class/Helper.h"

using namespace std;

class Path {
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
	Path(vector<Coordinate> v) {
		pathVal = v;
		setNameBasedOnPath(pathVal);
	}

	double getPathLength(){
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



void grabLetter(vector<Coordinate>, vector<Coordinate>);
void lastTwo(vector<Coordinate>, vector<Coordinate>);

vector<Coordinate> availCoor;	
vector<Coordinate> currentPath = {};
vector<::Path> allPaths = {};



int main()
{
	srand(time(NULL));

	int x;
	cout << "How many inputs would you like?" << endl;
	cin >> x;
	cout << endl;

	
	for (int i = 0; i < x; i++) {
		char c = 'A';
		c += i;
		///int x = rand
		string s(1, c);
		int randomNumber1 = (rand() % 100) + 1;
		int randomNumber2 = (rand() % 100) + 1;
		Coordinate CO = Coordinate(s, randomNumber1, randomNumber2);
		availCoor.push_back(CO);
	}


	grabLetter(availCoor, currentPath);


	std::sort(allPaths.begin(), allPaths.end(), []( ::Path& a, ::Path& b) {
			return a.getPathLength() < b.getPathLength(); // ascending order
		});

	std::cout << "Starting to display: " << endl;
	std::cout  << endl;
	for (int i = 0; i < allPaths.size(); i++) {
		
			std::cout << allPaths.at(i).getName() << " : ";
			std::cout << allPaths.at(i).getPathLength();
		
		std::cout << endl;
	}
}


void grabLetter(vector<Coordinate> AvailLettParamVal, vector<Coordinate> currentPathParamVal) {


	int totalAvailLetters = 0;


	for (int i = 0; i < AvailLettParamVal.size(); i++) {
		
		if (AvailLettParamVal.at(i).getName() != "x") {
			totalAvailLetters++;
		}
	}

	if (totalAvailLetters == 2) {
	
		lastTwo(AvailLettParamVal, currentPathParamVal);
	}

	for (int i = 0; i < AvailLettParamVal.size(); i++) {
		if (AvailLettParamVal.at(i).getName() == "x") {
			continue;
		}

		
		Coordinate c = AvailLettParamVal.at(i);
		currentPathParamVal.push_back(c);
		AvailLettParamVal.at(i).setName("x");
		grabLetter(AvailLettParamVal, currentPathParamVal);
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
	
	One.push_back( AvailLettParamVal.at(first) );
	One.push_back(AvailLettParamVal.at(second));

	Two.push_back(AvailLettParamVal.at(second));
	Two.push_back(AvailLettParamVal.at(first));

	Path onePath = Path(One);
	Path twoPath = Path(Two);

	allPaths.push_back(onePath);
	allPaths.push_back(twoPath);
}


