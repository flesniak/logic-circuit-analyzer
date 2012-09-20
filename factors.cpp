#include "factors.h"

Factors::Factors()
{
    //Set environment defaults
    p_circVoltage = 1.2;
    p_circTemperature = 55;

    //Initialize factor maps
    p_voltageMap[1.08] = 1.121557;
    p_voltageMap[1.12] = 1.075332;
    p_voltageMap[1.16] = 1.035161;
    p_voltageMap[1.20] = 1;
    p_voltageMap[1.24] = 0.968480;
    p_voltageMap[1.28] = 0.940065;
    p_voltageMap[1.32] = 0.914482;

    p_tempMap[-25] = 0.897498;
    p_tempMap[-15] = 0.917532;
    p_tempMap[0] = 0.948338;
    p_tempMap[15] = 0.979213;
    p_tempMap[25] = 1;
    p_tempMap[35] = 1.020305;
    p_tempMap[45] = 1.040540;
    p_tempMap[55] = 1.061831;
    p_tempMap[65] = 1.082983;
    p_tempMap[75] = 1.103817;
    p_tempMap[85] = 1.124124;
    p_tempMap[95] = 1.144245;
    p_tempMap[105] = 1.164563;
    p_tempMap[115] = 1.184370;
    p_tempMap[125] = 1.204966;

    p_processMap[slow] = 1.174235;
    p_processMap[typical] = 1;
    p_processMap[fast] = 0.876148;
}

double Factors::getCircVoltage() const
{
    return p_circVoltage;
}

bool Factors::setCircVoltage(double voltage)
{
    if( p_voltageMap.count(voltage) == 0 )
        return false;
    else {
        p_circVoltage = voltage;
        return true;
    }
}

double Factors::getVoltageFactor() const
{
    return (*(p_voltageMap.find(p_circVoltage))).second;
}

double Factors::getCircTemperature() const
{
    return p_circTemperature;
}

bool Factors::setCircTemperature(double temp)
{
    if( p_tempMap.count(temp) == 0 )
        return false;
    else {
        p_circTemperature = temp;
        return true;
    }
}

double Factors::getTempFactor() const
{
    return (*(p_tempMap.find(p_circTemperature))).second;
}

processType Factors::getProcessType() const
{
    return p_processType;
}

bool Factors::setProcessType(processType type)
{
    if( p_processMap.count(type) == 0 )
        return false;
    else {
        p_processType = type;
        return true;
    }
}

double Factors::getProcessFactor() const
{
    return (*(p_processMap.find(p_processType))).second;
}

void Factors::getFactors(double &voltageFactor, double &tempFactor, double &processFactor)
{
    voltageFactor = getVoltageFactor();
    tempFactor = getTempFactor();
    processFactor = getProcessFactor();
}

string Factors::processTypeToString(processType type)
{
    switch( type ) {
        case slow : return "Slow";
        case typical : return "Typical";
        case fast : return "Fast";
    };
}
