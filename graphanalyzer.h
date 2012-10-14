#ifndef GRAPHANALYZER_H
#define GRAPHANALYZER_H

#include <map>
#include <string>

using namespace std;

class Library;
class GraphCreator;
class Factors;
class GateElement;

class GraphAnalyzer
{
    public:
        GraphAnalyzer(Library* library, Factors* factors, GraphCreator* graphCreator);
        ~GraphAnalyzer();
        bool analyze();
        string getOutputPath() const;
        string getTransitionPath() const;
        double getOutputPathRuntime() const;
        double getTransitionPathRuntime() const;
        double getMaxFrequency() const;

    private:
        Library* p_library;
        Factors* p_factors;
        GraphCreator* p_graphCreator;
        struct dfsData {
            GateElement* predecessor;
            double pathRuntime;
        };
        map<GateElement*,dfsData> p_dfsCache;
        double p_outputPathRuntime;
        double p_transitionPathRuntime;
        string p_outputPath;
        string p_transitionPath;

        bool calculateBaseTimes();
        bool doDfs(GateElement* element, GateElement* start);
        string createSequenceString(GateElement* last, GateElement* first);
};

#endif
