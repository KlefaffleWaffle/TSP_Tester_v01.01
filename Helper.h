#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <vector>

using namespace std;

class Helper {
private:
	
	//Called by debug message
	static string removeLeftWhiteSpace(string& s);

public:

	static int displayYN();
	static int displayChoice(string s, string s2);
	//.h returns actual value typed.
	static int displayChoiceVector(vector<string>);

	//Use this one if you always want to display a cycle option. i.e. "5. More Options"
	static int displayChoiceVectorCycle(vector<string>, int size, int more = 4);

	static void readFromVector(vector<string> v, int pos);

	// In progress;
	//static int displayChoiceVectorLarge(vector<string> list, int startPos, vector<string> alwaysShow, vector<int> overrideNumbers);

	//static void pause(); - cin.ignore

	static void debugMessage(string fileName, int, string message, int key);

};



class Coordinate {
private:
	int x;
	int y;
	string name;
public:
	Coordinate(string nameParam, int xParam, int yParam) {
		x = xParam;
		y = yParam;
		name = nameParam;
	}

	Coordinate( int xParam, int yParam) {
		x = xParam;
		y = yParam;
	}

	void setX(int xP) {
		x = xP;
	}

	void setY(int yP) {
		y = yP;
	}

	void setName(string nameP) {
		name = nameP;
	}

	int getX() {
		return x;
	}

	int getY() {
		return y;
	}

	string getName() {
		return name;
	}
};


#endif
