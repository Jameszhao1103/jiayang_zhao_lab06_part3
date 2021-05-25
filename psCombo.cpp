#include <iomanip>
#include "psCombo.h"
#include "visitor.h"


/* print state data - as aggregate of all incidents in this state */
std::ostream& operator<<(std::ostream &out, const psCombo& PD) {
    out << "State Info: " << PD.printState();
    out << "\nNumber of incidents: " << PD.getNumberOfCases();
    out << std::setprecision(2) << std::fixed;
    out << "\nIncidents with age";
    out << "\n(over 65): " << PD.getCasesOver65() << " %: " << PD.getCasesOver65()/double(PD.getNumberOfCases())*100;
    out << "\n(19 to 64): " << PD.getNumberOfCases()-PD.getCasesOver65()-PD.getCasesUnder18() << " %: " << (PD.getNumberOfCases()-PD.getCasesOver65()-PD.getCasesUnder18())/double(PD.getNumberOfCases())*100;
    out << "\n(under 18): " << PD.getCasesUnder18() << " %: " << PD.getCasesUnder18()/double(PD.getNumberOfCases())*100;
    out << "\nIncidents involving fleeing: " << PD.getFleeingCount() << " %: " << PD.getFleeingCount()/double(PD.getNumberOfCases())*100;
    out << "\nIncidents involving mental illness: " << PD.getNumMentalI() << " %: " << PD.getNumMentalI()/double(PD.getNumberOfCases())*100;
    out << "\nMale incidents: " << PD.getnumMales() << " female incidents: " << PD.getnumFemales();
    out << "\nRacial demographics of state incidents: " << PD.getRacialData();
    return out;
}

void psCombo::accept(class Visitor &v){
    v.visit(shared_from_this());
}