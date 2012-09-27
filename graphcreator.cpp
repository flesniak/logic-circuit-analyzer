#include "graphcreator.h"

#include "listelement.h"
#include "gateelement.h"
#include "library.h"
#include "signallistcreator.h"
#include "signal.h"

#include <iostream>

GraphCreator::GraphCreator(Library* library, SignalListCreator* signalListCreator)
    : p_library(library), p_signalListCreator(signalListCreator), p_firstElement(0), p_lastElement(0)
{
}

bool GraphCreator::createGraph()
{
        std::cout << "DEBUG: createGraph" << endl;
    deleteGraph();
    p_signalListCreator->createSignalList();
    if( p_signalListCreator->p_signalList.empty() )
        return false; //signalList empty, error!

    for(vector<Signal*>::iterator it = p_signalListCreator->p_signalList.begin(); it != p_signalListCreator->p_signalList.end(); it++) {
            std::cout << "DEBUG: processing signal source " << it-p_signalListCreator->p_signalList.begin() << " type " << (*it)->getSignalType() << endl;
        ListElement* newElement = 0;
        if( (*it)->getSignalType() != Signal::input ) {
            newElement = searchElement( (*it)->getSource() ); //maybe this element already exists with an invalid gateType

        if( newElement ) { //our element already exists, the gatetype must be invalid
                std::cout << "DEBUG: element already exists: " << newElement << endl;
            newElement->getGateElement()->setGateType( p_library->getGate( (*it)->getSourceType() ) );
        }
        else {
            newElement = new ListElement( new GateElement( p_library->getGate( (*it)->getSourceType() ), (*it)->getSource() ) );
                std::cout << "DEBUG: created new ListElement " << newElement << endl;
            if( p_firstElement ) {
                std::cout << "DEBUG: new ListElement appended to " << p_lastElement << endl;
                p_lastElement->setNextElement( newElement ); //firstElement already exists
            }
            else {
                std::cout << "DEBUG: new ListElement is firstElement!" << endl;
                p_firstElement = newElement; //we don't have any firstElement, this one is it!
            }
            p_lastElement = newElement; //currently last item in the list
        }
        switch( (*it)->getSignalType() ) {
            case Signal::output : newElement->getGateElement()->setIsOutputElement(true);
                break;
            case Signal::input : newElement->getGateElement()->setIsInputElement(true);
                break;
            default : break;
        };
        }
        for(unsigned int i = 0; i < (*it)->getTargetCount(); i++) {
                std::cout << "DEBUG: processing target " << (*it)->getTarget(i) << endl;
            ListElement* successor = searchElement( (*it)->getTarget(i) );
            if( successor == 0 ) {
                successor = new ListElement( new GateElement( 0, (*it)->getTarget(i) ) ); //create target gate without type
                p_lastElement->setNextElement(successor);
                p_lastElement = successor;
            }
            if( (*it)->getSignalType() != Signal::input )
                newElement->getGateElement()->addSuccessor(successor->getGateElement());
        }
        cout << "------------------------------ gate complete" << endl;
    }
    return true;
}

void GraphCreator::deleteGraph()
{
        std::cout << "DEBUG: deleteGraph" << endl;
    while( p_firstElement != p_lastElement ) {
        ListElement* temp = p_firstElement->getNextElement();
        delete p_firstElement;
        p_firstElement = temp;
    }
    if( p_firstElement != 0 )
        delete p_firstElement;
    p_firstElement = p_lastElement = 0;
}

ListElement* GraphCreator::searchElement(const string& name) const
{
    for( ListElement* element = p_firstElement; element != p_lastElement; element = element->getNextElement() ) {
            //std::cout << "DEBUG: searching for " << name << " first last " << p_firstElement << " " << p_lastElement << " element " << element << endl;
            //sleep(1);
        if( element->getGateElement()->getName() == name )
            return element;
        }
    return 0;
}

const ListElement* GraphCreator::getFirstElement()
{
    if( p_firstElement == 0 )
        createGraph();
    return p_firstElement;
}
