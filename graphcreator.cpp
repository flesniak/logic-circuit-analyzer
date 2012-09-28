#include "graphcreator.h"

#include "listelement.h"
#include "gateelement.h"
#include "library.h"
#include "signallistcreator.h"
#include "signal.h"

GraphCreator::GraphCreator(Library* library, SignalListCreator* signalListCreator)
    : p_library(library), p_signalListCreator(signalListCreator), p_firstElement(0), p_lastElement(0)
{
}

bool GraphCreator::createGraph()
{
    deleteGraph();
    p_signalListCreator->createSignalList();
    if( p_signalListCreator->p_signalList.empty() )
        return false; //signalList empty, error!

    for(vector<Signal*>::iterator it = p_signalListCreator->p_signalList.begin(); it != p_signalListCreator->p_signalList.end(); it++) {
        ListElement* newElement = 0;
        if( (*it)->getSignalType() != Signal::input ) { //input signals don't have a source gate, only adjust targets!
            newElement = searchElement( (*it)->getSource() ); //maybe this element already exists with an invalid gateType
            if( newElement ) //our element already exists, the gatetype must be invalid
                newElement->getGateElement()->setGateType( p_library->getGate( (*it)->getSourceType() ) );
            else {
                newElement = new ListElement( new GateElement( p_library->getGate( (*it)->getSourceType() ), (*it)->getSource() ) );
                insertElement(newElement);
            }
            if( (*it)->getSignalType() == Signal::output )
                newElement->getGateElement()->setIsOutputElement(true);
        }
        for(unsigned int i = 0; i < (*it)->getTargetCount(); i++) { //no need to escape output elements, these shall not have targets
            ListElement* successor = searchElement( (*it)->getTarget(i) );
            if( successor == 0 ) {
                successor = new ListElement( new GateElement( 0, (*it)->getTarget(i) ) ); //create target gate without type
                insertElement(successor);
            }
            if( (*it)->getSignalType() == Signal::input ) //dealing with an input signal, set every target as input
                successor->getGateElement()->setIsInputElement(true);
            else //input signals don't have a source
                newElement->getGateElement()->addSuccessor(successor->getGateElement());
        }
    }
    return true;
}

void GraphCreator::deleteGraph()
{
    while( p_firstElement != p_lastElement ) {
        ListElement* temp = p_firstElement->getNextElement();
        delete p_firstElement;
        p_firstElement = temp;
    }
    if( p_firstElement != 0 )
        delete p_firstElement;
    p_firstElement = p_lastElement = 0;
}

void GraphCreator::insertElement(ListElement* element) {
    if( p_lastElement )
        p_lastElement->setNextElement(element);
    else
        p_firstElement = element;
    p_lastElement = element; //now last item in the list
}

ListElement* GraphCreator::searchElement(const string& name) const
{
    for( ListElement* element = p_firstElement; element != 0; element = element->getNextElement() )
        if( element->getGateElement()->getName() == name )
            return element;
    return 0;
}

const ListElement* GraphCreator::getFirstElement()
{
    if( p_firstElement == 0 )
        createGraph();
    return p_firstElement;
}
