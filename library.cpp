#include "library.h"

#include <iostream>
#include <sstream>

#include "gate.h"
#include "flipflop.h"

Library::Library() : p_loaded(false)
{
    p_libraryPath = "bib.txt";
}

Library::~Library()
{
    closeLibrary();
}

void Library::closeLibrary()
{
    if( fileReader.is_open() )
        fileReader.close();
    p_loaded = false;
}

bool Library::setLibraryPath(string path)
{
    closeLibrary();
    p_libraryPath = path;
    return tryOpenLibraryFile();
}

string Library::getLibraryPath() const
{
    return p_libraryPath;
}

bool Library::parseLibraryFile()
{
    if( !fileReader.is_open() && !tryOpenLibraryFile() )
        return false;
    fileReader.seekg(0);
    string line, name;
    double tpd0;
    short ei, kl, cl, tsetup, thold, ct;
    while( !fileReader.eof() ) {
        getline(fileReader,line);
        if( line.size() < 2 //drop empty or 1-char lines
         || line[0] == '#' || line[0] == '/' //drop comments
         || (name.empty() && line[0] != '[') //while searching for a part, drop lines with trash
         || line.substr(0,2) == "[[" ) //drop [[-Elements
            continue;
        if( !name.empty() ) { //Processing part ...
            if( line[0] == '[' ) { //Part complete, save it!
                if( ei == 0 || tpd0 == 0 || cl == 0 || kl == 0 || (tsetup+thold+ct > 0 && (tsetup == 0 || thold == 0 || ct == 0)) ) {
                    cout << "WARNING: Incomplete part " << name << endl;
                }
                else {
                    if( tsetup+thold+ct > 0 ) //we have a flipflop!
                        p_gates.push_back(new Flipflop(name,tpd0,kl,cl,ei,tsetup,thold,ct));
                    else
                        p_gates.push_back(new Gate(name,tpd0,kl,cl,ei));
                }
                name.clear();
                tpd0 = ei = kl = cl = tsetup = thold = ct = 0;
            }
            size_t pos = line.find(':');
            string parameter = line.substr(0,pos-1);
            istringstream iss(line.substr(pos+1));
            if( pos == string::npos || parameter.empty() || iss.str().empty() ) {
                cout << "WARNING: Invalid value field " << line << ", skipping part " << name << endl;
                name.clear();
            }
            if( parameter == "ei" || parameter == "ed" )
                iss >> ei;
            if( parameter == "tpd0" || parameter == "tpdt" )
                iss >> tpd0;
            if( parameter == "kl" )
                iss >> kl;
            if( parameter == "cl" || parameter == "cd" )
                iss >> cl;
            if( parameter == "tsetup" )
                iss >> tsetup;
            if( parameter == "thold" )
                iss >> thold;
            if( parameter == "ct" )
                iss >> ct;
        }
        else { //Searching for part, we have a [-line
            size_t pos = line.find_last_of(']');
            if( pos == string::npos )
                cout << "WARNING: Invalid part " << line << endl;
            else
                name = line.substr(1,pos-1);
        }
    }
    return true;
}

bool Library::tryOpenLibraryFile()
{
    fileReader.open(p_libraryPath.c_str());
    if( fileReader.is_open() ) {
        parseLibraryFile();
        return true;
    } else {
        fileReader.close();
        p_loaded = false;
        return false;
    }
}

void Library::printLibraryFile()
{
    if( !fileReader.is_open() && !tryOpenLibraryFile() ) {
        cout << "Fehler beim Öffnen der Bibliotheks-Datei!" << endl;
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

void Library::printLibaryContents()
{
    if( p_gates.empty() && !parseLibraryFile() ) {
        cout << "Fehler beim Lesen der Bibliotheksdatei" << endl;
        return;
    }

}
