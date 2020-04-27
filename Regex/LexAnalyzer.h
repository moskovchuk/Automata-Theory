#pragma once
#include <map>
#include <regex>
#include <string>
#include <fstream>

using namespace std;

class LexAnalyzer {
private:
	string str;
	regex templateRg;
	map <string, int> statistic;
public:
	LexAnalyzer();
	~LexAnalyzer();
	bool check();
	void CheckString(istream& input, ofstream& output);
	void commit(bool outCode, ofstream& output) ;
	void saveStatistic(string& serverName);
	void printStatistic(ofstream& output);
};

