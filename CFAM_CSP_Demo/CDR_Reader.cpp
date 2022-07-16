#include "CDR_Reader.h"

void CDR_Reader::readCDRFile(string full_file_name)
{
	lines = setNumOfLines(full_file_name);
	ifstream CDR_Read_File(full_file_name);
	if (!CDR_Read_File.is_open()) {
		return;
	}
	string  line;
	dataStrings = new string[lines];
	int line_index = 0;
	while (line_index < lines) {
		if (getline(CDR_Read_File, line)) {
			dataStrings[line_index] = line;
		}
		line_index++;
	}
	CDR_Read_File.close();
}

string* CDR_Reader::getFileString()
{
	return dataStrings;
}

int CDR_Reader::setNumOfLines(string full_file_name)
{
	ifstream CDR_Read_File(full_file_name);
	if (!CDR_Read_File.is_open()) {
		return -1;
	}
	string  line;
	while (getline(CDR_Read_File, line)) {
		lines++;
	}
	CDR_Read_File.close();
	return lines;
}

int CDR_Reader::getNumOfLines()
{
	return lines;
}

string CDR_Reader::getLine()
{
	if (gIndex >= lines || gIndex < 0)
		gIndex = 0;
	string tmp = dataStrings[gIndex];
	gIndex++;
	return tmp;
}
