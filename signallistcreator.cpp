#include "signallistcreator.h"

#include <iostream>
#include <sstream>

SignalListCreator::SignalListCreator() : p_frequency(0)
{
    p_circuitPath = "csd.txt";
}

SignalListCreator::~SignalListCreator()
{
    if( fileReader.is_open() )
        fileReader.close();
}

void SignalListCreator::clear()
{
    p_frequency = 0;
    for(vector<Signal*>::iterator it = p_signalList.begin(); it != p_signalList.end(); it++)
        delete *it;
    p_signalList.clear();
}

string SignalListCreator::getCircuitPath() const
{
    return p_circuitPath;
}

bool SignalListCreator::setCircuitPath(string path)
{
    clear();
    p_circuitPath = path;
    return tryOpenFile();
}

bool SignalListCreator::tryOpenFile()
{
    if( fileReader.is_open() )
        fileReader.close();
    fileReader.open(p_circuitPath.c_str());
    return fileReader.is_open();
}

void SignalListCreator::printCircuitFile()
{
    if( !fileReader.is_open() && !tryOpenFile() ) {
        cout << "Fehler beim Öffnen der Schaltwerksdatei!" << endl;
        return;
    }
    fileReader.seekg(0);
    unsigned int lineCount = 1;
    string str;
    while( !fileReader.eof() ) {
        getline(fileReader, str);
        cout << lineCount++ << ": " << str << endl;
    }
}

void SignalListCreator::printSignals()
{
    if( p_signalList.empty() && !createSignalList() ) {
        cout << "Fehler beim Öffnen der Schaltwerksdatei!";
        return;
    }
    vector<Signal*>::iterator it = p_signalList.begin();
    while( it != p_signalList.end() ) {
        ostringstream oss;
        oss << it-p_signalList.begin()+1;
        cout << "Signal: s"+oss.str()+" | Quelle: ";
        if( (*it)->getSource().empty() )
            cout << "Keine";
        else
            cout << (*it)->getSource() << " (" << (*it)->getSourceType() << ")";
        cout << " | Typ: ";
        switch( (*it)->getSignalType() ) {
            case Signal::internal : cout << "Intern";
                break;
            case Signal::output : cout << "Output";
                break;
            case Signal::input : cout << "Input";
                break;
            default : break;
        };
        cout << " | Zielgatter: ";
        if( !(*it)->getTargetCount() )
            cout << "Keine";
        else
            for(int i=(*it)->getTargetCount(); i>0; i--) {
                cout << (*it)->getTarget(i-1);
                if( i )
                    cout << " ";
            }
        cout << endl;
        it++;
    }
}

long SignalListCreator::getFrequency() const
{
    return p_frequency;
}

vector<Signal*> SignalListCreator::getSignalList()
{
    if( p_signalList.empty() )
        createSignalList();
    return p_signalList;
}

unsigned int SignalListCreator::getSignalCount()
{
    if( p_signalList.empty() )
        createSignalList();
    return p_signalList.size();
}

bool SignalListCreator::createSignalList()
{
    if( !fileReader.is_open() && !tryOpenFile() )
        return false;
    fileReader.seekg(0);
    p_frequency = 0;
    p_signalList.clear();
    string line;
    p_error = false;
    while( !fileReader.eof() && !p_error ) {
        getline(fileReader,line);
        if( line.size() > 2 && line.substr(0,2) == "//" ) //drop comments
            continue;
        if( line.size() > 12 && line.substr(0,13) == "ARCHITECTURE" ) //drop ARCH line
            continue;
        if( line.size() > 5 && line.substr(0,6) == "ENTITY" ) //drop entity
            continue;
        if( line.size() > 5 && line.substr(0,5) == "CLOCK" ) {
            line = line.substr(line.find(", ")+1);
            istringstream iss(line.substr(0,line.find(';')));
            iss >> p_frequency;
            line.clear();
            iss >> line;
            if( line == "GHz" )
                p_frequency *= 1000000000;
            if( line == "MHz" )
                p_frequency *= 1000000;
            if( line == "kHz" )
                p_frequency *= 1000;
            continue;
        }
        if( line.size() > 4 && line.substr(0,5) == "BEGIN" )
            continue;
        if( line.size() > 2 && line.substr(0,3) == "END" )
            continue;
        parseSignalLine(line,"INPUT",Signal::input);
        parseSignalLine(line,"OUTPUT",Signal::output);
        parseSignalLine(line,"SIGNALS",Signal::internal);
        parseGateLine(line);
    }
    return !p_error;
}

void SignalListCreator::parseSignalLine(string &line, string keyword, Signal::signalTypes signalType)
{
    if( !(line.size() > keyword.size()+1) || !(line.substr(0,keyword.size()+1) == keyword+" ") ) //do nothing on invalid strings
        return;
    line = line.substr(keyword.size()+1); //crop KEYWORD and space
    line = line.substr(0,line.find_last_of(';')); //crop ;
    while( !line.empty() ) {
        size_t pos = line.rfind(',');
        if( pos != string::npos ) {
            keyword = line.substr(pos+1);
            line = line.substr(0,line.size()-keyword.size()-1);
        }
        else {
            keyword = line;
            line.clear();
        }
        if( keyword.length() == 4 ) {
            istringstream iss(keyword.substr(1,3));
            unsigned int index;
            iss >> index;
            while( p_signalList.size() < index ) //taking care on correct signal numeration
                p_signalList.push_back(new Signal);
            p_signalList.at(index-1)->setSignalType(signalType);
        }
    }
}

void SignalListCreator::parseGateLine(string &line)
{
    if( !(line.size() > 4) || !(line[0] == 'g') )
        return;
    string gateName = line.substr(0,4);
    string gateType = line.substr(line.find(':')+1,line.find('(')-line.find(':')-1);
    string signals = line.substr(line.find('(')+1,line.find(')')-line.find('(')-1);
    if( signals.size() < 4 || gateType.empty() )
        return;
    while( !signals.empty() ) {
        size_t pos = signals.find(',');
        string signalStr = signals.substr(0,pos);
        if( pos == string::npos )
            signals.clear();
        else
            signals.erase(0,pos+1);
        if( signalStr.empty() || signalStr == "clk" || signalStr[0] != 's' )
            continue;
        istringstream iss(signalStr.substr(1));
        unsigned int index;
        iss >> index;
        if( p_signalList.size() < index || index == 0 ) //signal invalid
            continue;
        if( signals.empty() ) { //last line entry is source
            if( !p_signalList.at(index-1)->getSource().empty() ) {
                cout << "FEHLER: Signal " << signalStr << " hat zwei Quellen!" << endl;
                p_error = true;
            }
            p_signalList.at(index-1)->setSource(gateName);
            p_signalList.at(index-1)->setSourceType(gateType);
        } else {
            if( p_signalList.at(index-1)->hasTarget(gateName) )
                cout << "WARNUNG: Signal " << signalStr << " hat Gate " << gateName << " zweimal als Ziel. Wird ignoriert." << endl; //no need to set p_error here!
            else
                p_signalList.at(index-1)->addTarget(gateName);
        }
    }
}
