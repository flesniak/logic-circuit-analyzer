#!/bin/bash
g++ -c -o graphanalyzer.o graphanalyzer.cpp &&
g++ -c -o factors.o factors.cpp &&
g++ -c -o flipflop.o flipflop.cpp &&
g++ -c -o gate.o gate.cpp &&
g++ -c -o gateelement.o gateelement.cpp &&
g++ -c -o graphcreator.o graphcreator.cpp &&
g++ -c -o library.o library.cpp &&
g++ -c -o listelement.o listelement.cpp &&
g++ -c -o menu.o menu.cpp &&
g++ -c -o signal.o signal.cpp &&
g++ -c -o signallistcreator.o signallistcreator.cpp &&
g++ -o lca main.cpp -I. factors.o flipflop.o gate.o gateelement.o graphcreator.o library.o listelement.o menu.o signal.o signallistcreator.o graphanalyzer.o
