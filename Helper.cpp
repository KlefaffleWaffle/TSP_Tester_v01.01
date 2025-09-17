
#include "Helper.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int Helper::displayYN() {
	int x;
	x = Helper::displayChoice("Yes", "No");
	return x;
}

int Helper::displayChoice(string s1, string s2) {
	cout << "1. " << s1 << "\n2. " << s2 << "\n\n";;
	int x;
	cin >> x;
	return x;
}

//Returns actual value typed. Not coded value;
int Helper::displayChoiceVector(vector<string> v) {

	for (int i = 0; i < v.size(); i++) {
		cout << (i + 1) << ". " << v.at(i) << "\n";
	}
	cout << "\n";

	int x;
	cin >> x;
	return x;
}



int Helper::displayChoiceVectorCycle(vector<string> v, int size, int more) {
	//size represents how many options we want to display. i.e. if size is 5, we display 5 options.
	//more represents the option we always want displayed. (Assumes always at bottom. Generally, we will assume this means more options hence the name)
	// 

	//Line between new vs Old
	// 

	//we have 11 options. In English we are saying, display 4 options, and then the special one. 

	int start = 0;
	int fin = start + size - 1;
	int pos = -27;

	int x;
	do {

		for (int iter = 0, pos = start; iter < size; iter++, pos++) {

			// if iterator is not last and the overall position is the special value.
			if (iter != (size - 1) && pos == more) {
				iter--;
				cout << "may display more" << endl;
				continue;
			}

			//if the overall position is at the final spot in the display.
					//This is what it does, what is it supposed to do.
			if (iter == (size - 1)) {
				cout << more + 1 << ". " << v.at(more) << endl;

				//if overall postion is greater than the vecotrs size
			}
			else if (pos >= v.size()) {
				cout << "" << endl;

				//otherwise display as normal. 
			}
			else {
				cout << pos + 1 << ". " << v.at(pos) << endl;
			}
		}
		cout << endl;

		start = fin;


		if (start >= v.size()) {
			start = 0;
		}
		fin = start + size;

		cin >> x;
	} while (x == more + 1);

	return x;


	//===============================================

		//Trying to make this iterative not recursive, ergo, no starting pos.

		//display four items at a time.
		//skip the parameter item. Default fifth.

		//this do is just saying keep calling display until you get exit code.



	/*
	int startingPos = 0;

		bool endOfVector = false;
		do{
			//this is the sub routine that actually displays
			//we use +4 b/c 5th is reserved.
			if(endOfVector == true){
				startingPos = 0;
				endOfVector = false;
			}else{

				for(int i = startingPos; i < startingPos+4; i++){
					if(startingPos == pos){
					startingPos++;
					break;
					}

					if(i < v.size()){
						cout << i+1 <<". " <<v.at(i)<<endl;
					}else{
					cout << endl;
					endOfVector = true;
					}
				}
				cout << pos+1 <<". " << v.at(pos)<<endl;
			}
			int r=-27;
			cin >> r;
		}while(r != pos+1);

		*/
	return -27;
}

void Helper::readFromVector(vector<string> v, int pos) {
	cout << v.at(pos);
}

string Helper::removeLeftWhiteSpace(string& s) {
	auto start = find_if(s.begin(), s.end(), [](unsigned char ch) {return !isspace(ch); });
	return string(start, s.end());
}

void Helper::debugMessage(string FILENAME, int type, string message, int key) {
	//Recommended: Make "FILENAME" a constant in the program calling this function.
	//         string mFILEPATH = "C:\\Users\\[YOUR NAME]\\source\\repos\\TSP Tester\\TSP Tester.cpp";
	// 
	//Type: 0 = No prefix, 1 = AJD Error:, 2 = AJD Warning
	//This program uses message to find itself, but verifies with Key.
	//		It is recommended to make keys big numbers.

	cout << endl;
	string x = "";


	ifstream thisFile(FILENAME);  // open for reading

	if (!thisFile) {
		cerr << "Error opening file!" << endl;
		return;
	}

	string line;
	int i = 0;
	while (getline(thisFile, line)) {
		i++;
		string trimmed = (line);

		//cout << "Line is : " << trimmed << endl;
		if (trimmed.find("Helper::debugMessage") != string::npos) {
			//DO NOT DELETE BELOW COMMENT. May use for debugging.
			//cout << "Found debug functions in file " << FILENAME << endl;

			size_t pos1 = trimmed.find(message);
			if (pos1 != string::npos) {

				size_t pos2 = trimmed.find(to_string(key));
				if (pos2 != string::npos) {
				
					switch (type) {
					case 0:
						cout << "\t" << message << endl;
						break;
					case 1:
						cout << "\tAJD ERROR: " << message << endl;
						break;
					case 2:
						cout << "\tAJD WARNING: " << message << endl;
						break;
					}

					cout << "\t\tFound message at line: " << i << endl<<endl;
					
				}
				else {
					cout << "\tFound message at line: " << i << " But with wrong key. \n\tPlease update message" << endl;
				}
				break;

			}
			else {
				continue;
			}

		}
		

	}

	thisFile.close(); 
}