#ifndef FLIPFLOP_H
#define FLIPFLOP_H

#include "gate.h"

class Flipflop : public Gate
{
    public:
        Flipflop(const string& name,
                 const double tpd0,
                 const short loadFactor,
                 const short loadCapacity,
                 const short inputCount,
                 const short setupTime,
                 const short holdTime,
                 const short loadCapacityClock);
        ~Flipflop();
        bool getIsFlipflop() const;
        short getSetupTime() const;
        short getHoldTime() const;
        short getLoadCapacityClock() const;
    private:
        const short p_setupTime;
        const short p_holdTime;
        const short p_loadCapacityClock;
};

#endif // FLIPFLOP_H
