#include "graphanalyzer.h"

#include "library.h"
#include "factors.h"
#include "graphcreator.h"
#include "gateelement.h"
#include "listelement.h"

GraphAnalyzer::GraphAnalyzer(Library* library, Factors* factors, GraphCreator* graphCreator)
    : p_library(library), p_factors(factors), p_graphCreator(graphCreator)
{
}

GraphAnalyzer::~GraphAnalyzer()
{
}

bool GraphAnalyzer::analyze()
{
    if( !calculateBaseTimes() )
	return false;
    for( ListElement* element = p_graphCreator->getFirstElement(); element != 0; element = element->getNextElement() )
	if( element->getGateElement()->getIsInputElement() || element->getGateElement()->getGateType()->getIsFlipflop() ) { //valid start point
	    dfsCache.clear(); //reset all cached data
	    doDfs(element->getGateElement(), element->getGateElement());
	}
}

void GraphAnalyzer::doDfs(GateElement* element, GateElement* start)
{
    vector<GateElement*> successors = element->getSuccessors();
    for(vector<GateElement*>::iterator it = successors.begin(); it != successors.end(); it++) {
	if( (*it)->getGateType()->getIsFlipflop() )
    }
}

bool GraphAnalyzer::calculateBaseTimes()
{
    double p_tempFactors = p_factors->getTempFactor()*p_factors->getVoltageFactor()*p_factors->getProcessFactor();
    for(ListElement* element = p_graphCreator->getFirstElement(); element != 0; element = element->getNextElement())
	element->getGateElement()->setBaseRuntime( p_tempFactors * 
						  (element->getGateElement()->getGateType()->getBaseTime() +
						   element->getGateElement()->getGateType()->getLoadFactor() *
						   element->getGateElement()->getGateType()->getLoadCapacity()) );
    return true;
}

