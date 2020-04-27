#include "AppClass.h"

using namespace std;

AppClass::AppClass() : _fsm(*this), isAcceptable(false), tmpStr(), nameServer(), tmpType(), nameZone(), statistic() {
#ifdef FSM_DEBUG
#ifdef CRTP
	setDebugFlag(true);
#else
	_fsm.setDebugFlag(true);
#endif
#endif
}

bool  AppClass::CheckString(string& inputStr) {
	_fsm.enterStartState();
    _fsm.restart();
	for (int i = 0; i < inputStr.length(); i++) {
        if ((inputStr[i] >= 'a' && inputStr[i] <= 'z') || (inputStr[i] >= 'A' && inputStr[i] <= 'Z')) {
            _fsm.letter(char(inputStr[i]));
            continue;
        }
        if (inputStr[i] >= '0' && inputStr[i] <= '9') {   
            _fsm.digit(char(inputStr[i]));
            continue;
        }
        if (inputStr[i] == ':') {
            _fsm.dots(':');
            continue;
        }
        if (inputStr[i] == '?') {
            _fsm.question('?');
            continue;
        }
        if (inputStr[i] == '.') {
            _fsm.dot('.');
            continue;
        }
        if (inputStr[i] == '@') {
            _fsm.dog('@');
            continue;
        }
        if (inputStr[i] == '=') {
            _fsm.equal('=');
            continue;
        }
    }
	_fsm.EOS();
	return isAcceptable;
}

void AppClass::AppendStr(char tmp) {
    tmpStr.append(1,tmp);
}

void AppClass::AppendServer(char tmp) {
    tmpStr.append(1,tmp);
    nameServer.append(1,tmp);
}

void AppClass::AppendZone(char tmp) {
    tmpStr.append(1,tmp);
    nameZone.append(1,tmp);
}
void AppClass::AppendType(char tmp) {
    tmpStr.append(1,tmp);
    tmpType.append(1,tmp);
}

void AppClass::setAcceptable() {
    isAcceptable = true;
}

void AppClass::UpdateStatistic() {
    if (statistic.find(nameServer) == statistic.end())
        statistic.insert(pair<string, int>(nameServer, 1));
    else
        statistic[nameServer]++;
}

bool AppClass::type() {
    transform(tmpType.begin(), tmpType.end(), tmpType.begin(), ::tolower);
    if ((tmpType == "talk") || (tmpType == "chat"))
        return true;
    else
        return false;
}

bool AppClass::title() {
    transform(tmpStr.begin(), tmpStr.end(), tmpStr.begin(), ::tolower);
    if (tmpStr == "gtalk")
        return true;
    else
        return false;
}

bool AppClass::NotTooLong() {
    if (nameZone.length() > 0 && nameZone.length() <= 5)
        return true;
    else
        return false;
}

void AppClass::ClearCash() {
    isAcceptable = false;
    tmpStr.clear();
    tmpType.clear();
    nameServer.clear();
    nameZone.clear();
}

string& AppClass::getStr() {
    return tmpStr;
}

void AppClass::printStatistic(ofstream& output) {
    auto it = statistic.begin();
    for (; it != statistic.end(); it++)
        output << "Server name: \"" << it->first << "\" encountered " << it->second << endl;
}