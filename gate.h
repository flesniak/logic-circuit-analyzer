#ifndef GATE_H
#define GATE_H

#include <string>

using namespace std;

class Gate
{
    public:
        Gate(const string& name,
             const double tpd0,
             const short loadFactor,
             const short loadCapacity,
             const short inputCount);
        ~Gate();

        string getName() const;
        double getBaseTime() const;
        short getLoadFactor() const;
        short getLoadCapacity() const;
        short getInputCount() const;
        virtual bool getIsFlipflop() const;
    private:
        const string p_name;
        const double p_tpd0;
        const short p_loadFactor;
        const short p_loadCapacity;
        const short p_inputCount;
};

#endif // GATE_H
