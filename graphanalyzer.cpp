#include "graphanalyzer.h"

#include "library.h"
#include "factors.h"
#include "graphcreator.h"
#include "gateelement.h"
#include "listelement.h"
#include "flipflop.h"

#include <iostream>

GraphAnalyzer::GraphAnalyzer(Library* library, Factors* factors, GraphCreator* graphCreator)
    : p_library(library), p_factors(factors), p_graphCreator(graphCreator), p_outputPathRuntime(0), p_transitionPathRuntime(0)
{
}

GraphAnalyzer::~GraphAnalyzer()
{
}

bool GraphAnalyzer::analyze()
{
    if( p_graphCreator->getFirstElement() == 0 ) //graphCreator unsuccessful
        return false;
    if( !calculateBaseTimes() )
        return false;
    p_outputPath.clear();
    p_transitionPath.clear();
    p_outputPathRuntime = p_transitionPathRuntime = 0;
    for( ListElement* element = p_graphCreator->getFirstElement(); element != 0; element = element->getNextElement() )
        if( element->getGateElement()->getIsInputElement() || element->getGateElement()->getGateType()->getIsFlipflop() ) { //valid start point
            p_dfsCache.clear(); //reset all cached data
            doDfs(element->getGateElement(), element->getGateElement());
        }
	return true;
}

void GraphAnalyzer::doDfs(GateElement* element, GateElement* start)
{
    vector<GateElement*> successors = element->getSuccessors();
    for(vector<GateElement*>::iterator it = successors.begin(); it != successors.end(); it++)
        if( (*it)->getGateType()->getIsFlipflop() ) {
            if( p_transitionPathRuntime < element->getBaseRuntime() + p_dfsCache[element].pathRuntime ) {
                p_transitionPathRuntime = element->getBaseRuntime() + p_dfsCache[element].pathRuntime;
                p_transitionPath = createSequenceString(element,start) + "->" + (*it)->getName(); //*it not in dfsCache yet, add it manually
            }
        } else {
            if( p_dfsCache[*it].pathRuntime < p_dfsCache[element].pathRuntime + element->getBaseRuntime() ) {
                if( ( p_dfsCache[*it].pathRuntime || *it == start ) && p_dfsCache[*it].predecessor != element ) {
                    p_dfsCache[*it].predecessor = element;
                    if( traceBack(*it,element) )
                        cout << "DEBUG: *it " << *it << " element " << element << " start " << start << endl;
                }
                p_dfsCache[*it].pathRuntime = p_dfsCache[element].pathRuntime + element->getBaseRuntime();
                p_dfsCache[*it].predecessor = element;
                doDfs(*it,start);
            }
        }
    if( element->getIsOutputElement() && p_outputPathRuntime < p_dfsCache[element].pathRuntime + element->getBaseRuntime() ) {
        p_outputPathRuntime = p_dfsCache[element].pathRuntime + element->getBaseRuntime();
        p_outputPath = createSequenceString(element,start);
    }
}

bool GraphAnalyzer::traceBack(GateElement* element, GateElement* target) //tries to go from element to target, but the reverse way!
{
    while( element && !element->getGateType()->getIsFlipflop() ) {
        if( element == target )
            return true;
        element = p_dfsCache[element].predecessor;
    }
    return false;
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
    double tempFactors = p_factors->getTempFactor()*p_factors->getVoltageFactor()*p_factors->getProcessFactor();
    for(ListElement* element = p_graphCreator->getFirstElement(); element != 0; element = element->getNextElement()) {
        vector<GateElement*> successors = element->getGateElement()->getSuccessors();
        double cLoad = 0;
        for(vector<GateElement*>::iterator it = successors.begin(); it != successors.end(); it++)
            cLoad += (*it)->getGateType()->getLoadCapacity();
        element->getGateElement()->setBaseRuntime( tempFactors *
                                                 ( element->getGateElement()->getGateType()->getBaseTime() +
                                                   element->getGateElement()->getGateType()->getLoadFactor() *
                                                   cLoad / 1000.0 ) );
    }
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
    if( p_transitionPathRuntime == 0 )
        return 0;
    return 1.0e12/( p_transitionPathRuntime + static_cast<const Flipflop*>(p_library->getGate("dff"))->getSetupTime() );
}
