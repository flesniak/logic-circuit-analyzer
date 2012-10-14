#ifndef GATEELEMENT_H
#define GATEELEMENT_H

#include "gate.h"

#include <vector>

class GateElement
{
    public:
        GateElement(const Gate* gateType, const string& name);
        string getName() const;
        const Gate* const getGateType() const;
        GateElement* getSuccessor(unsigned int index) const;
        unsigned int getSuccessorCount() const;
        vector<GateElement*> getSuccessors() const;
        bool getIsOutputElement() const;
        bool getIsInputElement() const;
        double getBaseRuntime() const;
        unsigned short getConnectedInputCount() const;
        void addSuccessor(GateElement* successor);
        void setIsOutputElement(bool output);
        void setIsInputElement(bool input);
        void setGateType(const Gate* gateType);
        void setBaseRuntime(double runtime);
        void setConnectedInputCount(unsigned short count);
        void incConnectedInputCount();
    private:
        const string p_name;
        const Gate* p_gateType;
        vector<GateElement*> p_successors;
        bool p_isInputElement;
        bool p_isOutputElement;
        double p_baseRuntime;
        unsigned short p_connectedInputs;
};

#endif // GATEELEMENT_H
