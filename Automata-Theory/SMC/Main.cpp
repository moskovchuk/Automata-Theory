#include "AppClass.h"
#include <ctime>

using namespace std;

int main(int argc, char* argv[]) {
    ifstream input;
    ofstream output;
    ofstream statistic;
    if (argc > 2) {
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
	AppClass scanString;
    string tmp;
    //--------------------------------------------------------------------
    while (getline(input, tmp)) {
        _time = time(0);
        bool result = scanString.CheckString(tmp);
        all += time(0) - _time;
        if (result)
            output << "Acceptable string! " << scanString.getStr() << endl;
        else
            output << "Unacceptable string! " << scanString.getStr() << endl;        
    }
    statistic << "Elapsed time: " << all << " seconds (" << clock() - _clock << " clock ticks).\n" << endl << endl;
    scanString.printStatistic(statistic);
	input.close();
	output.close();
	statistic.close();
    return 0;
}
