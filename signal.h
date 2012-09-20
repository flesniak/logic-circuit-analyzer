#ifndef SIGNAL_H
#define SIGNAL_H

#include <string>
#include <vector>

using namespace std;

class Signal
{
    public:
        Signal();
        ~Signal();
        enum signalTypes { input, //input signals don't have a source
                           output, //output signals don't have targets
                           internal, //internal signals have both source and targets
                           none };
        unsigned int getTargetCount() const;
        string getTarget(unsigned int index) const;
        string getSource() const;
        string getSourceType() const;
        signalTypes getSignalType() const;
        void setSource(string source);
        void setSourceType(string sourceType);
        void setTargets(vector<string> targets);
        void addTarget(string target);
        void setSignalType(signalTypes signalType);
        bool hasTarget(const string& target) const;

    private:
        signalTypes p_signalType;
        vector<string> p_targets;
        string p_source;
        string p_sourceType;
};

#endif // SIGNAL_H
