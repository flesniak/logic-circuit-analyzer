#ifndef SIGNALLISTCREATOR_H
#define SIGNALLISTCREATOR_H

#include <string>
#include <vector>
#include <fstream>

#include "signal.h"

using namespace std;

class SignalListCreator
{
    public:
        SignalListCreator();
        ~SignalListCreator();
        bool setCircuitPath(string path);
        string getCircuitPath() const;
        void printCircuitFile();
        void printSignals();

        vector<Signal*> getSignalList();
        unsigned int getSignalCount();
        long getFrequency() const;

        friend class GraphCreator;

    private:
        bool createSignalList();
        void parseCommaLine(string &line, string keyword, Signal::signalTypes signalType);
        void parseGateLine(string &line);
        bool tryOpenFile();
        ifstream fileReader;
        string p_circuitPath;
        vector<Signal*> p_signalList;
        long p_frequency;
};

#endif // SIGNALLISTCREATOR_H
