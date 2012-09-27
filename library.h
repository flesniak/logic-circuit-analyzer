#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <fstream>
#include <vector>

class Gate;

using namespace std;

class Library
{
    public:
        Library();
        ~Library();
        bool setLibraryPath(string path);
        string getLibraryPath() const;
        void closeLibrary();
        void printLibraryFile();
        void printLibaryContents();
        const Gate* getGate(const string& name) const;

    private:
        bool parseLibraryFile();
        bool tryOpenLibraryFile();
        void clearLibrary();
        string p_libraryPath;
        ifstream fileReader;
        vector<const Gate*> p_gates;
};

#endif // LIBRARY_H
