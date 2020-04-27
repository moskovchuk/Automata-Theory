%option noyywrap
%option c++
%x SERVER ERROR TAIL

%{
    #ifndef NLEXER_H
    #define NLEXER_H
    
    #if !defined(yyFlexLexerOnce)
    #include <FlexLexer.h>
    #endif
    #include <iostream>
	#include <fstream>
	#include <string>
	#include <map>
	#include <ctime>
    #include <sstream>

	using namespace std;
	
	class AppClass {
	private:
		string tmpStr;
		string nameServer;
		map<string, int> statistic;
	public:
		AppClass();
		~AppClass();
		void ClearCash();
		void AddStr(string& tmp);
		void setServerName(string& tmp);
		void saveStatistic();
		void printStatistic(ofstream& output);
		const string getStr();
	};
	
	AppClass::AppClass() : nameServer(), tmpStr() {}
	
	AppClass::~AppClass() {
        nameServer.clear();		
        statistic.clear();
		tmpStr.clear();
	}

	void AppClass::AddStr(string& tmp) {
		tmpStr += tmp;
	}
		
	void AppClass::ClearCash() {
        nameServer.clear();
		tmpStr.clear();
	}
	
	void AppClass::setServerName(string& tmp) {
		nameServer = tmp;
	}

	void AppClass::saveStatistic() {
		if (statistic.find(nameServer) == statistic.end())
			statistic.insert(pair<string, int>(nameServer, 1));
		else
			statistic[nameServer]++;
	}

	void AppClass::printStatistic(ofstream& output) {
		auto it = statistic.begin();
		for (; it != statistic.end(); it++)
			output << "Server name: \"" << it->first << "\" encountered " << it->second << endl;
	}

	const string AppClass::getStr() {
		return tmpStr;
	}

	AppClass FlexAnalyzer;
	ifstream input;
	ofstream output;
	yyFlexLexer ftp(&input, &output);
    #endif
%}

letter [A-Za-z]
digit  [0-9]
term   (({letter}|{digit})+)

%%
<INITIAL>{
	(?i:gtalk\:(talk|chat)\?jid={term}@) {
		string tmp = yytext;
		FlexAnalyzer.ClearCash();
		FlexAnalyzer.AddStr(tmp);
		BEGIN(SERVER);
	}
	. {
		string tmp = yytext;
		FlexAnalyzer.ClearCash();
		FlexAnalyzer.AddStr(tmp);
		BEGIN(ERROR);
	}
	\n {
		string tmp = yytext;
		FlexAnalyzer.ClearCash();
		FlexAnalyzer.AddStr(tmp);
		BEGIN(INITIAL);
		return 0;
	}
	<<EOF>> {
		return -1;
	}
}

<SERVER>{
	{term} {
		string tmp = yytext;
		FlexAnalyzer.AddStr(tmp);
		FlexAnalyzer.setServerName(tmp);
		BEGIN(TAIL);
	}
	. {
		string tmp = yytext;
		FlexAnalyzer.AddStr(tmp);
		BEGIN(ERROR);
	}
	\n {
		string tmp = yytext;
		FlexAnalyzer.AddStr(tmp);
		BEGIN(INITIAL);
		return 0;
	}
	<<EOF>> {
		return -1;
	}
}

<TAIL>{
	\.{letter}{1,5}(\n) {
		bool check = false;
		string tmp = yytext;
		FlexAnalyzer.AddStr(tmp);
		FlexAnalyzer.saveStatistic();
		BEGIN(INITIAL);
		return 1;
	}
	. {
		string tmp = yytext;
		FlexAnalyzer.AddStr(tmp);
		BEGIN(ERROR);
	}
	<<EOF>> {
		return -1;
	}
}

<ERROR>{
	\n {
		string tmp = yytext;  
		FlexAnalyzer.AddStr(tmp);
		BEGIN(INITIAL);
		return 0;
	}
    . {
		string tmp = yytext;  
		FlexAnalyzer.AddStr(tmp);
	};
    <<EOF>> {
		return -1;
	}
}
%%

int main(int argc, char* argv[]) {
	std::ofstream statistic;
    if(argc > 2) {
        input.open(argv[1]);
        output.open(argv[2]);
        statistic.open(argv[3]);     
    } 
    else {
        cout << "Not enough arguments!" << endl;
        return 1;
    }
    if(!(input.is_open() && output.is_open() && statistic.is_open())){
    	cout << "Error of openning files!" << endl;
        return -1;
    }
    clock_t _clock = clock();
	time_t _time = time(0);
    time_t all = 0;
	
	int result = 0;
	while (result != -1) {
        _time = time(0);
		result = ftp.yylex();
        all += _time - time(0);
		switch (result) {
			case 1:
				output << "Acceptable string! " << FlexAnalyzer.getStr();
				continue;
			case 0:
				output << "Unacceptable string! " << FlexAnalyzer.getStr();
			case -1:
				break;
		}
	}
    statistic << "Elapsed time: " << all << " seconds (" << clock() - _clock << " clock ticks)." << endl << endl;
	FlexAnalyzer.printStatistic(statistic);
	input.close();
	output.close();
	statistic.close();
	return 0;
}
