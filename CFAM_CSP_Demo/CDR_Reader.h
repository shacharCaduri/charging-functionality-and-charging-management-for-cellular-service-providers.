#pragma once
#include <string>
#include <fstream>
using namespace std;

class CDR_Reader
{
private:
	string* dataStrings;
	int lines;
	int gIndex;
	int setNumOfLines(string full_file_name);
	void readCDRFile(string full_file_name);

public:
	CDR_Reader(string path) {
		dataStrings = NULL;
		lines = 0;
		gIndex = 0;
		readCDRFile(path);
	}

	~CDR_Reader() {
		delete[] dataStrings;
	}


	string* getFileString();

	int getNumOfLines();

	string getLine();
};
