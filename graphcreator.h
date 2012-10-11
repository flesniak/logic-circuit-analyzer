#ifndef GRAPHCREATOR_H
#define GRAPHCREATOR_H

#include <string>

using namespace std;

class Library;
class SignalListCreator;
class ListElement;

class GraphCreator
{
    public:
        GraphCreator(Library* library, SignalListCreator* signalListCreator);
        ListElement* getFirstElement();
        void deleteGraph();
    private:
        Library* p_library;
        SignalListCreator* p_signalListCreator;
        ListElement* p_firstElement;
        ListElement* p_lastElement;
        bool createGraph();
        ListElement* searchElement(const string& name) const;
        void insertElement(ListElement* element);
};

#endif // GRAPHCREATOR_H
