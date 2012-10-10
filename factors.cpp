#include "factors.h"

#include <cmath>

Factors::Factors()
{
    //Set environment defaults
    p_circVoltage = 120;
    p_circTemperature = 55;
    p_processType = slow; //typical

    //Initialize factor maps
    p_voltageMap[108] = 1.121557;
    p_voltageMap[112] = 1.075332;
    p_voltageMap[116] = 1.035161;
    p_voltageMap[120] = 1;
    p_voltageMap[124] = 0.968480;
    p_voltageMap[128] = 0.940065;
    p_voltageMap[132] = 0.914482;

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
    if( voltage < -25 || voltage > 125 )
        return false;
    p_circVoltage = voltage*100; //internal centi-Volts
    return true;
}

double Factors::getVoltageFactor() const
{
    const short delta = 4;
    const short lowest = 108;
    const short upper = ceil((p_circVoltage-lowest)/delta)*delta+lowest;
    const short lower = floor((p_circVoltage-lowest)/delta)*delta+lowest;
    const double m = ( (*(p_voltageMap.find(upper))).second - (*(p_voltageMap.find(lower))).second ) / delta;
    return (*(p_voltageMap.find(lower))).second + m * (p_circVoltage - lower);
}

double Factors::getCircTemperature() const
{
    return p_circTemperature;
}

bool Factors::setCircTemperature(double temp)
{
    if( temp < -25 || temp > 125 )
        return false;
    p_circTemperature = temp;
    return true;
}
#include <iostream>
using namespace std;
double Factors::getTempFactor() const
{
    const short lowest = -25;
    short delta, upper, lower;
    if( p_circTemperature > -15 && p_circTemperature < 0 ) { //fuzzy workaround for non-linear distributed values
        delta = 15;
        upper = 0;
        lower = -15;
    } else if( p_circTemperature > 0 && p_circTemperature < 15 ) {
        delta = 15;
        upper = 15;
        lower = 0;
    } else {
        delta = 10;
        upper = ceil((p_circTemperature-lowest)/delta)*delta+lowest;
        lower = floor((p_circTemperature-lowest)/delta)*delta+lowest;
    }
    const double m = ( (*(p_tempMap.find(upper))).second - (*(p_tempMap.find(lower))).second ) / delta;
    return (*(p_tempMap.find(lower))).second + m * (p_circTemperature - lower);
}

processType Factors::getProcessType() const
{
    return p_processType;
}

bool Factors::setProcessType(processType type)
{
    if( p_processMap.count(type) ) {
        p_processType = type;
        return true;
    }
    return false;
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
        default : return string();
    };
}
