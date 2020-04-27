#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "LexAnalyzer.h"

using namespace std;

int main(int argc, char* argv[]) {
    ifstream input;
    ofstream output;
    ofstream Statistic;
    if (argc > 2) {
        input.open(argv[1]);
        output.open(argv[2]);  
        Statistic.open(argv[3]);
    }
    else {
        cout << "Not enough arguments!" << endl;
        return 1;
    }
    if(!(input.is_open() && output.is_open() && Statistic.is_open())){
    	cout << "Error of openning files!" << endl;
        return -1;
    }
	LexAnalyzer Context;
	clock_t _clock = clock();
	time_t _time;
	time_t all = 0;
	_time = time(0);
	while (!input.eof()) {
		_time = time(0);
		Context.CheckString(input, output);
		all += time(0) - _time;
	}
	Statistic << "Elapsed time: " << all << " seconds (" << clock() - _clock << " clock ticks)." << endl << endl;
	Context.printStatistic(Statistic);
	input.close();
	output.close();
	Statistic.close();
	return 0;
}
