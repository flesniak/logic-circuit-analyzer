#include "graphanalyzer.h"

#include "library.h"
#include "factors.h"
#include "graphcreator.h"
#include "gateelement.h"
#include "listelement.h"

#include <iostream>
using namespace std;

GraphAnalyzer::GraphAnalyzer(Library* library, Factors* factors, GraphCreator* graphCreator)
    : p_library(library), p_factors(factors), p_graphCreator(graphCreator), p_outputPathRuntime(0), p_transitionPathRuntime(0)
{
}

GraphAnalyzer::~GraphAnalyzer()
{
}

bool GraphAnalyzer::analyze()
{
    if( !calculateBaseTimes() )
        return false;
    p_outputPath.clear();
    p_transitionPath.clear();
    p_outputPathRuntime = p_transitionPathRuntime = 0;
    for( ListElement* element = p_graphCreator->getFirstElement(); element != 0; element = element->getNextElement() )
        if( element->getGateElement()->getIsInputElement() || element->getGateElement()->getGateType()->getIsFlipflop() ) { //valid start point
            p_dfsCache.clear(); //reset all cached data
            //cout << "DEBUG: Init doDfs for " << element->getGateElement()->getName() << endl;
            doDfs(element->getGateElement(), element->getGateElement());
        }
	return true;
}

void GraphAnalyzer::doDfs(GateElement* element, GateElement* start)
{
    vector<GateElement*> successors = element->getSuccessors();
    for(vector<GateElement*>::iterator it = successors.begin(); it != successors.end(); it++)
            //cout << "DEBUG: processing successor " << (*it)->getName() << " of " << element->getName() << endl;
        if( (*it)->getGateType()->getIsFlipflop() ) {
            //cout << "DEBUG: entering flipflop handling..." << endl;
            if( p_transitionPathRuntime < element->getBaseRuntime() + p_dfsCache[element].pathRuntime ) {
                p_transitionPathRuntime = element->getBaseRuntime() + p_dfsCache[element].pathRuntime;
                p_transitionPath = createSequenceString(element,start) + "->" + (*it)->getName(); //*it not in dfsCache yet, add it manually
                    cout << "DEBUG: new transition " << p_transitionPathRuntime << endl;
            }
        } else {
                //cout << "DEBUG: entering default handling..." << endl;
            if( p_dfsCache[*it].pathRuntime < p_dfsCache[element].pathRuntime + element->getBaseRuntime() ) {
                    //cout << "DEBUG: pathRuntime smaller, increasing..." << endl;
                if( ( p_dfsCache[*it].pathRuntime || *it == start ) && p_dfsCache[*it].predecessor != element ) {
                    p_dfsCache[*it].predecessor = element;
                    //if(  ) do cycleSearch
                }
                p_dfsCache[*it].pathRuntime = p_dfsCache[element].pathRuntime + element->getBaseRuntime();
                p_dfsCache[*it].predecessor = element;
                doDfs(*it,start);
            }
        }
    if( element->getIsOutputElement() && p_outputPathRuntime < p_dfsCache[element].pathRuntime + element->getBaseRuntime() ) {
            //cout << "DEBUG: output element handling..." << endl;
        p_outputPathRuntime = p_dfsCache[element].pathRuntime + element->getBaseRuntime();
        p_outputPath = createSequenceString(element,start);
            cout << "DEBUG: new output " << p_outputPathRuntime << endl;
    }
        //cout << "DEBUG: element " << element->getName() << " complete" << endl;
}

string GraphAnalyzer::createSequenceString(GateElement* last, GateElement* first)
{
    if( last != first )
        return createSequenceString(p_dfsCache[last].predecessor,first) + "->" + last->getName();
    else
        return last->getName();
}

bool GraphAnalyzer::calculateBaseTimes()
{
    double p_tempFactors = p_factors->getTempFactor()*p_factors->getVoltageFactor()*p_factors->getProcessFactor();
    for(ListElement* element = p_graphCreator->getFirstElement(); element != 0; element = element->getNextElement())
        element->getGateElement()->setBaseRuntime( p_tempFactors *
                                                  (element->getGateElement()->getGateType()->getBaseTime() +
                                                   element->getGateElement()->getGateType()->getLoadFactor() *
                                                   element->getGateElement()->getGateType()->getLoadCapacity() / 1000.0) );
    return true;
}

string GraphAnalyzer::getOutputPath() const
{
    return p_outputPath;
}

string GraphAnalyzer::getTransitionPath() const
{
    return p_transitionPath;
}

double GraphAnalyzer::getOutputPathRuntime() const
{
    return p_outputPathRuntime;
}

double GraphAnalyzer::getTransitionPathRuntime() const
{
    return p_transitionPathRuntime;
}

double GraphAnalyzer::getMaxFrequency() const
{
    return 0;
}
