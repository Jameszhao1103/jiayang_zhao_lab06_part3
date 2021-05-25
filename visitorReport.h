#ifndef VISITREP_H
#define VISITREP_H

#include "psData.h"
#include "demogData.h"
#include "visitor.h"
#include <iomanip>

class visitorReport : public Visitor {
public:
    visitorReport() : numVisited(0) {}

	void visit(demogData *e) {
       //print out the data
            cout << std::setprecision(2) << std::fixed;
            cout << "print summary demog Data:" << endl;
            cout << "Region info: comboData, " << e->getState();
            cout << "\nEducation info:";
            cout << "\n(Bachelor or more): " << e->getBAup();
            cout <<  "% and total: " << e->getBAupCount();
            cout << "\n(high school or more): " << e->getHSup();
            cout <<  "% and total: " << e->getHSupCount();
            cout << "\nTotal population: " << e->getPop() << endl;
            cout << e->getRaceData() << endl;
    }
    
    void visit(psData *e) {
        cout << "hello" << endl;
    }

    void visit(psCombo *e) {
        cout << "print aggregate police shooting data " << endl;
            cout << "State Info: " << e->printState();
            cout << "\nNumber of incidents: " << e->getNumberOfCases();
            cout << std::setprecision(2) << std::fixed;
            cout << "\nRacial demographics of state incidents: " << e->getRacialData() << endl;
    }

    private:
    	int numVisited;
};

#endif