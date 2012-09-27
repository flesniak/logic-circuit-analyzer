#include "listelement.h"

ListElement::ListElement(GateElement* gateElement)
    : p_gateElement(gateElement), p_next(0)
{
}

GateElement* ListElement::getGateElement() const
{
    return p_gateElement;
}

ListElement* ListElement::getNextElement() const
{
    return p_next;
}

void ListElement::setGateElement(GateElement* gateElement)
{
    p_gateElement = gateElement;
}

void ListElement::setNextElement(ListElement* nextListElement)
{
    p_next = nextListElement;
}
