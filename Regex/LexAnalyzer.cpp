#include "LexAnalyzer.h"
#include <iostream>
#include <sstream>

LexAnalyzer::LexAnalyzer() : templateRg("^gtalk\\:(talk|chat)\\?jid=([a-zA-Z0-9]+)@([a-zA-Z0-9]+)\\.([a-zA-Z]{1,5})$", std::regex_constants::icase), str() {}

LexAnalyzer::~LexAnalyzer() {
	str.clear();
	statistic.clear();
}

bool LexAnalyzer::check() {
	bool result = false;
	smatch splitInGroup;
	result = regex_match(str, splitInGroup, templateRg);
	if (result) {
		string serverName = splitInGroup[3];
		saveStatistic(serverName);
	}
	return result;
}

void LexAnalyzer::CheckString(istream& input, ofstream& output) {
	getline(input, str);
	bool result = check();
	commit(result, output);
	str.clear();
}

void LexAnalyzer::saveStatistic(string& serverName) {
	if (statistic.find(serverName) == statistic.end())
		statistic.insert(pair<string, int>(serverName, 1));
	else
		statistic[serverName]++;
}

void LexAnalyzer::commit(bool outCode, ofstream& output) {
	if (outCode)
		output << "Acceptable string! \"" << str << "\"\n";
	else
		output << "Unacceptable string! \"" << str << "\"\n";
}

void LexAnalyzer::printStatistic(ofstream& output) {
	auto it = statistic.begin();
	for (; it != statistic.end(); it++)
		output << "Server name: \"" << it->first << "\" encountered " << it->second << endl;
}