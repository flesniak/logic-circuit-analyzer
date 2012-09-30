#ifndef GRAPHANALYZER_H
#define GRAPHANALYZER_H

#include <map>

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

    private:
	Library* p_library;
	Factors* p_factors;
	GraphCreator* p_graphCreator;
	struct dfsData {
	    GateElement* predecessor = 0;
	    double pathRuntime = 0;
	};
	map<GateElement*,dfsData> dfsCache;

	bool calculateBaseTimes();
	void doDfs(GateElement* element, GateElement* start);
};

#endif
