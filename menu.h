#ifndef MENU_H
#define MENU_H

#include "factors.h"
#include "library.h"
#include "signallistcreator.h"

#include <string>

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

        void factorsMenu();
        void libraryMenu();
        void circuitMenu();
        void analyze();
};

#endif // MENU_H
