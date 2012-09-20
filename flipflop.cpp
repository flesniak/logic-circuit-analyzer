#include "flipflop.h"

Flipflop::Flipflop(const string& name,
                   const double tpd0,
                   const short loadFactor,
                   const short loadCapacity,
                   const short inputCount,
                   const short setupTime,
                   const short holdTime,
                   const short loadCapacityClock)
                 : Gate(name,tpd0,loadFactor,loadCapacity,inputCount),
                   p_setupTime(setupTime),
                   p_holdTime(holdTime),
                   p_loadCapacityClock(loadCapacityClock)
{
}

Flipflop::~Flipflop()
{
}

bool Flipflop::getIsFlipflop() const
{
    return true;
}

short Flipflop::getSetupTime() const
{
    return p_setupTime;
}

short Flipflop::getHoldTime() const
{
    return p_holdTime;
}

short Flipflop::getLoadCapacityClock() const
{
    return p_loadCapacityClock;
}
