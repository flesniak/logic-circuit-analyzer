#include "gateelement.h"

GateElement::GateElement(const Gate* gateType, const string& name)
    : p_name(name), p_gateType(gateType), p_isInputElement(false), p_isOutputElement(false)
{
}

string GateElement::getName() const
{
    return p_name;
}

const Gate* const GateElement::getGateType() const
{
    return p_gateType;
}

GateElement* GateElement::getSuccessor(unsigned int index) const
{
    if( p_successors.size() <= index )
        return 0;
    else
        return p_successors[index];
}

unsigned int GateElement::getSuccessorCount() const
{
    return p_successors.size();
}

vector<GateElement*> GateElement::getSuccessors() const
{
    return p_successors;
}

bool GateElement::getIsOutputElement() const
{
    return p_isOutputElement;
}

bool GateElement::getIsInputElement() const
{
    return p_isInputElement;
}

void GateElement::addSuccessor(GateElement* successor)
{
    p_successors.push_back(successor);
}

void GateElement::setIsOutputElement(bool output)
{
    p_isOutputElement = output;
}

void GateElement::setIsInputElement(bool input)
{
    p_isInputElement = input;
}

void GateElement::setGateType(const Gate* const gateType)
{
    p_gateType = gateType;
}
