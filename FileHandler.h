#ifndef CALENDAR_FILEHANDLER_H
#define CALENDAR_FILEHANDLER_H


#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <string>

using namespace std;

class FileHandler{

private:

	ifstream file;
	ofstream outFile;

	int mode;

public:

	static const int OUT_MODE = 0;
    static const int OUT_REWRITE_MODE = 2;
	static const int IN_MODE = 1;
    static const int IN_OUT_MODE = 3;

	FileHandler(const string& filepath, int mode);
	~FileHandler();
    void putHolidayToFile(int date, int month, int year, const string& holiday);
    vector<string> getHolidaysFromFile(int month, int year,bool defolt);
    void deleteHoliday(int day, int month, int year);
    void close();

private:

    string filepath;

};

#endif
