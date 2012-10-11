#include "graphcreator.h"

#include "listelement.h"
#include "gateelement.h"
#include "library.h"
#include "signallistcreator.h"
#include "signal.h"

#include <iostream>
#include <iomanip>

GraphCreator::GraphCreator(Library* library, SignalListCreator* signalListCreator)
    : p_library(library), p_signalListCreator(signalListCreator), p_firstElement(0), p_lastElement(0)
{
}

bool GraphCreator::createGraph()
{
    deleteGraph();
    if( !p_signalListCreator->createSignalList() )
        return false;
    if( p_signalListCreator->p_signalList.empty() )
        return false; //signalList empty, error!

    for(vector<Signal*>::iterator it = p_signalListCreator->p_signalList.begin(); it != p_signalListCreator->p_signalList.end(); it++) {
        while( it != p_signalListCreator->p_signalList.end() && (*it)->getSource().empty() && (*it)->getTargetCount() == 0 ) {
            cout << "WARNUNG: Signal s" << setfill('0') << setw(3) << (int)(it-p_signalListCreator->p_signalList.begin()+1) << " hat weder Quelle noch Ziel. Wird ignoriert, dadurch wird die Signalnummerierung geändert." << endl;
            delete *it;
            p_signalListCreator->p_signalList.erase(it);
        }
        ListElement* newElement = 0;
        if( (*it)->getSignalType() != Signal::input ) { //input signals don't have a source gate, only adjust targets!
            newElement = searchElement( (*it)->getSource() ); //maybe this element already exists with an invalid gateType
            if( newElement ) { //our element already exists, the gatetype must be invalid
                if( newElement->getGateElement()->getGateType() ) { //gatetype already specified, this is an error!
                    cout << "FEHLER: Gatter " << newElement->getGateElement()->getName() << " hat mehrere Signale am Ausgang (Kurzschluss)!" << endl;
                    return false;
                }
                newElement->getGateElement()->setGateType( p_library->getGate( (*it)->getSourceType() ) );
            }
            else {
                newElement = new ListElement( new GateElement( p_library->getGate( (*it)->getSourceType() ), (*it)->getSource() ) );
                insertElement(newElement);
            }
            if( (*it)->getSignalType() == Signal::output )
                newElement->getGateElement()->setIsOutputElement(true);
        }
        for(unsigned int i = 0; i < (*it)->getTargetCount(); i++) { //process targets of newElement
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
    //for(ListElement* element = p_firstElement; element != 0; element = element->getNextElement) {
    //    if( element->getGateElement()->getSuccessorCount() > element->getGateElement->getGateType()->getInputCount() )
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

ListElement* GraphCreator::getFirstElement()
{
    if( p_firstElement == 0 )
        createGraph();
    return p_firstElement;
}
