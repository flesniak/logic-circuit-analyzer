#include "gateelement.h"

GateElement::GateElement(const Gate* gateType, const string& name)
    : p_name(name), p_gateType(gateType), p_isInputElement(false), p_isOutputElement(false), p_baseRuntime(0), p_connectedInputs(0)
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

void GateElement::setGateType(const Gate* gateType)
{
    p_gateType = gateType;
}

double GateElement::getBaseRuntime() const
{
    return p_baseRuntime;
}

void GateElement::setBaseRuntime(double runtime)
{
    p_baseRuntime = runtime;
}

unsigned short GateElement::getConnectedInputCount() const
{
    return p_connectedInputs;
}

void GateElement::setConnectedInputCount(unsigned short count)
{
    p_connectedInputs = count;
}

void GateElement::incConnectedInputCount()
{
    p_connectedInputs++;
}
