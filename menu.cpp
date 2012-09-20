#include "menu.h"

#include <iostream>

//static const char *header = "******************************************\n*      IT-Projektpraktikum WS12/13       *\n* Laufzeitanalyse synchroner Schaltwerke *\n******************************************\n";
static const char *header = "PIT 2012/13\n";

Menu::Menu()
{
    p_factors = new Factors;
    p_library = new Library;
    p_signalListCreator = new SignalListCreator;
}

void Menu::displayMenu()
{
    bool exit = false;
    while( !exit ) {
            cout << header << endl;

            cout << "(1) Äußere Faktoren" << endl;
            cout << "    Spannung [Volt] = " << p_factors->getCircVoltage() << endl;
            cout << "    Temperatur [°C] = " << p_factors->getCircTemperature() << endl;
            cout << "    Prozesstyp: " << p_factors->processTypeToString(p_factors->getProcessType()) << endl;
            //cout << endl;

            cout << "(2) Bibliothek" << endl;
            cout << "    Pfad zur Bibliotheksdatei: " << p_library->getLibraryPath() << endl;
            //cout << endl;

            cout << "(3) Schaltwerk" << endl;
            cout << "    Pfad zur Schaltwerksdatei: " << p_signalListCreator->getCircuitPath() << endl;
            //cout << endl;

            cout << "(4) Analyse starten" << endl;
            //cout << endl;

            cout << "(5) Programm beenden" << endl;
            //cout << endl;

            cout << "Menüpunkt wählen: ";
            char answer;
            cin >> answer;
            cout << endl;
            switch( answer ) {
                case '1' : factorsMenu();
                           break;
                case '2' : libraryMenu();
                           break;
                case '3' : circuitMenu();
                           break;
                case '4' : analyze();
                           break;
                case '5' : exit = true;
                           break;
                default : cout << "Ungültige Eingabe" << endl;
            };
    }
}

void Menu::factorsMenu()
{
    bool exit = false;
    while( !exit ) {
            //cout << header << endl;

            cout << "Untermenü: Äußere Faktoren" << endl;
            cout << "(1) Spannung [Volt] = " << p_factors->getCircVoltage() << endl;
            cout << "(2) Temperatur [°C] = " << p_factors->getCircTemperature() << endl;
            cout << "(3) Prozesstyp: " << p_factors->processTypeToString(p_factors->getProcessType()) << endl;
            cout << "(4) Errechnete Faktoren ausgeben" << endl;
            cout << "(5) Hauptmenü" << endl;

            cout << "Untermenüpunkt wählen: ";
            char answer;
            cin >> answer;
            switch( answer ) {
                case '1' : cout << "Spannung [Volt] = ";
                           double voltage;
                           cin >> voltage;
                           if( p_factors->setCircVoltage(voltage) )
                                cout << "Spannung geändert auf " << voltage << " Volt." << endl;
                           else
                                cout << "Spannung ungültig. Keine Änderung vorgenommen." << endl;
                           break;
                case '2' : cout << "Temperatur [°C] = ";
                           double temp;
                           cin >> temp;
                           if( p_factors->setCircTemperature(temp) )
                               cout << "Temperatur geändert auf " << temp << "°C." << endl;
                           else
                               cout << "Temperatur ungültig. Keine Änderung vorgenommen." << endl;
                           break;
                case '3' : cout << "Neuer Prozesstyp: (";
                           for(unsigned short i = 0; i < 3; i++)
                            cout << i+1 << ": " << p_factors->processTypeToString((processType)i) << ", ";
                           cout << "): ";
                           short type;
                           cin >> type;
                           if( p_factors->setProcessType((processType)type) )
                                cout << "Prozesstyp geändert zu " << p_factors->processTypeToString((processType)type) << "(" << type << ") Volt." << endl;
                           else
                                cout << "Prozesstyp ungültig. Keine Änderung vorgenommen." << endl;
                           break;
                case '4' :
                           break;
                case '5' : exit = true;
                           break;
                default : cout << "Ungültige Eingabe" << endl;
            };
            cout << endl;
    }
}

void Menu::libraryMenu()
{
    bool exit = false;
    while( !exit ) {
            //cout << header << endl;

            cout << "Untermenü: Bibliothek" << endl;
            cout << "(1) Pfad zur Bibliotheksdatei: " << p_library->getLibraryPath() << endl;
            cout << "(2) Geladene Bauteile ausgeben" << endl;
            cout << "(3) Ausgabe der Bibliotheksdatei" << endl;
            cout << "(4) Hauptmenü" << endl;

            cout << "Untermenüpunkt wählen: ";
            char answer;
            cin >> answer;
            switch( answer ) {
                case '1' : {
                           bool ok = false;
                           while( !ok ) {
                               cout << "Pfad zur Bibliotheksdatei (Abbruch mit EXIT): ";
                               string path;
                               cin >> path;
                               if( path == "EXIT" )
                                   break;
                               p_library->closeLibrary();
                               if( p_library->setLibraryPath(path) ) {
                                   cout << "Bibliothek geöffnet: " << path << endl;
                                   ok = true;
                               }
                               else
                                   cout << "Konnte angegebene Datei nicht öffnen." << endl;
                           }
                           break;
                           }
                case '2' : p_library->printLibaryContents();
                           break;
                case '3' : p_library->printLibraryFile();
                           break;
                case '4' : exit = true;
                           break;
                default : cout << "Ungültige Eingabe" << endl;
            };
            cout << endl;
    }
}

void Menu::circuitMenu()
{
    bool exit = false;
    while( !exit ) {
            //cout << header << endl;

            cout << "Untermenü: Schaltwerk" << endl;
            cout << "(1) Pfad zur Schaltwerksdatei: " << p_signalListCreator->getCircuitPath() << endl;
            cout << "(2) Ausgabe der Schaltnetzdatei" << endl;
            cout << "(3) Ausgabe der Signale" << endl;
            cout << "(4) Ausgabe der Graphstruktur" << endl;
            cout << "(5) Hauptmenü" << endl;

            cout << "Untermenüpunkt wählen: ";
            char answer;
            cin >> answer;
            switch( answer ) {
                case '1' : while( true ) {
                               cout << "Pfad zur Schaltwerksdatei (Abbruch mit EXIT): ";
                               string path;
                               cin >> path;
                               if( path == "EXIT" )
                                   break;
                               if( p_signalListCreator->setCircuitPath(path) ) {
                                   cout << "Bibliothek geöffnet: " << path << endl;
                                   break;
                               }
                               else
                                   cout << "Konnte angegebene Datei nicht öffnen." << endl;
                           }
                           break;
                case '2' : p_signalListCreator->printCircuitFile();
                           break;
                case '3' : p_signalListCreator->printSignals();
                           break;
                case '4' : //p_signalListCreator->printSignals();
                           break;
                case '5' : exit = true;
                           break;
                default : cout << "Ungültige Eingabe" << endl;
            };
            cout << endl;
    }
}

void Menu::analyze()
{

}
