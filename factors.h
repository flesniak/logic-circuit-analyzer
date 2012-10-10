#ifndef FACTORS_H
#define FACTORS_H

#include <string>
#include <map>

using namespace std;

enum processType { slow, typical, fast };

class Factors
{
    public:
        Factors();
        double getCircVoltage() const;
        bool setCircVoltage(double voltage);
        double getCircTemperature() const;
        bool setCircTemperature(double temp);
        processType getProcessType() const;
        bool setProcessType(processType type);

        double getTempFactor() const;
        double getVoltageFactor() const;
        double getProcessFactor() const;
        void getFactors(double &voltageFactor, double &tempFactor, double &processFactor);

        static string processTypeToString(processType type);

    private:
        double p_circVoltage;
        double p_circTemperature;
        processType p_processType;
        map<short,double> p_voltageMap;
        map<short,double> p_tempMap;
        map<processType,double> p_processMap;
};

#endif // FACTORS_H
