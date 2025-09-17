

#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include <math.h>
#include <cstdlib> 
#include <ctime>   
#include <algorithm>
#include <fstream>
#include <filesystem>
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
string getDate();

vector<Coordinate> availCoor;	
vector<Coordinate> currentPath = {};
vector<::Path> allPaths = {};

string batchFilePath = "\"C:\\Users\\Austin\\Downloads\\klefafflewaffle.bat\" >nul 2>&1";


int main()
{
	srand(time(NULL));

	int x;
	cout << "How many inputs would you like?" << endl;
	cin >> x;
	cout << endl;

	system(batchFilePath.c_str());
	string path = getDate();
	string inputPath = path += "\\input.txt";
	

	std::ofstream outFile(inputPath.c_str());
	if (!outFile) {
		std::cerr << "Error opening file!" << std::endl;
		return 1;
	}

	for (int i = 0; i < x; i++) {
		char c = 'A';
		c += i;
		string s(1, c);
		int randomNumber1 = (rand() % 100) + 1;
		int randomNumber2 = (rand() % 100) + 1;
		cout << c << ": " << randomNumber1 << ", " << randomNumber2 << ", " << endl;
		outFile << c << ": " << randomNumber1 << ", " << randomNumber2 << std::endl;
		Coordinate CO = Coordinate(s, randomNumber1, randomNumber2);
		availCoor.push_back(CO);
	}

	outFile.close();

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


string getDate() {
	std::time_t t = std::time(nullptr);  // seconds since epoch
	std::tm now; // convert to local time

	localtime_s(&now, &t);

	string year = std::to_string(now.tm_year + 1900); // tm_year is years since 1900
	string month = std::to_string(now.tm_mon + 1);     // tm_mon is 0-11
	if (month.size() == 1) {
		month = "0" + month;
	}
	string day = std::to_string(now.tm_mday);
	string hour = std::to_string(now.tm_hour);
	string min = std::to_string(now.tm_min);
	string sec = std::to_string(now.tm_sec);

	

	string filePath = "D:\\TSP Tests\\";
	filePath += year;
	filePath += "\\";
	filePath += month;
	filePath += "\\";
	filePath += day;
	filePath += "\\";

	int i = 1;
	int latestFolder = 0;
	while (true) {
		std::string folder = filePath + "\\" + to_string(i);
		if (std::filesystem::exists(folder) && std::filesystem::is_directory(folder)) {
			latestFolder = i;
			i++;
		}
		else {
			break;
		}

	}
	filePath += to_string(latestFolder);
	



	return filePath;
}