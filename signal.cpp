#include "signal.h"

Signal::Signal() : p_signalType(none)
{
}

Signal::~Signal()
{
}

void Signal::addTarget(string target)
{
    p_targets.push_back(target);
}

Signal::signalTypes Signal::getSignalType() const
{
    return p_signalType;
}

string Signal::getSource() const
{
    return p_source;
}

string Signal::getSourceType() const
{
    return p_sourceType;
}

string Signal::getTarget(unsigned int index) const
{
    return p_targets.at(index);
}

unsigned int Signal::getTargetCount() const
{
    return p_targets.size();
}

void Signal::setSource(string source)
{
    p_source = source;
}

void Signal::setSourceType(string sourceType)
{
    p_sourceType = sourceType;
}

void Signal::setTargets(vector<string> targets)
{
    p_targets = targets;
}

void Signal::setSignalType(signalTypes signalType)
{
    p_signalType = signalType;
}

bool Signal::hasTarget(const string& target) const
{
    for(vector<string>::const_iterator it = p_targets.begin(); it != p_targets.end(); it++)
        if( *it == target )
            return true;
    return false;
}
