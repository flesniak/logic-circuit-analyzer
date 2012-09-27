#ifndef MENU_H
#define MENU_H

#include <string>

class Factors;
class Library;
class SignalListCreator;
class GraphCreator;

using namespace std;

class Menu
{
    public:
        Menu();
        void displayMenu();
    private:
        Factors *p_factors;
        Library *p_library;
        SignalListCreator *p_signalListCreator;
        GraphCreator* p_graphCreator;

        void factorsMenu();
        void libraryMenu();
        void circuitMenu();
        void analyze();
};

#endif // MENU_H
