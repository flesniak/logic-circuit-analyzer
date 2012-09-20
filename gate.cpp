#include "gate.h"

Gate::Gate(const string& name,
           const double tpd0,
           const short loadFactor,
           const short loadCapacity,
           const short inputCount)
         : p_name(name),
           p_tpd0(tpd0),
           p_loadFactor(loadFactor),
           p_loadCapacity(loadCapacity),
           p_inputCount(inputCount)
{
}

Gate::~Gate()
{
}

string Gate::getName() const
{
    return p_name;
}

double Gate::getBaseTime() const
{
    return p_tpd0;
}

short Gate::getLoadCapacity() const
{
    return p_loadCapacity;
}

short Gate::getLoadFactor() const
{
    return p_loadFactor;
}

short Gate::getInputCount() const
{
    return p_inputCount;
}

bool Gate::getIsFlipflop() const
{
    return false;
}
