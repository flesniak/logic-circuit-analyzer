#ifndef LISTELEMENT_H
#define LISTELEMENT_H

class GateElement;

class ListElement
{
    public:
        ListElement(GateElement* gateElement = 0);
        GateElement* getGateElement() const;
        ListElement* getNextElement() const;
        void setGateElement(GateElement* gateElement);
        void setNextElement(ListElement* nextListElement);
    private:
        GateElement* p_gateElement;
        ListElement* p_next;
};

#endif // LISTELEMENT_H
