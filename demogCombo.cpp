#include "demogCombo.h"
#include "demogData.h"
#include <sstream>
#include <string>
#include <assert.h>
#include <iomanip>
#include <math.h>

//add member functions here

/* print state data - as aggregate of all the county data */
std::ostream& operator<<(std::ostream &out, const demogCombo&SD) {
    out << "Combo Info: " << SD.printState();
    out << "\nNumber of Counties: " << SD.getNumberofcounty() << " County Demographics Info: "
        << "comboData, " << SD.getState();
    out << std::setprecision(2) << std::fixed;
    out << "\nPopulation info: \n(over 65): " << SD.getpopOver65()<< "\%";
    out <<  " and total: " << SD.getpopOver65Count();
    out << "\n(under 18): " << SD.getpopUnder18()<<"\%";
    out <<  " and total: " << SD.getpopUnder18Count();
    out << "\n(under 5): " << SD.getpopUnder5()<<"\%";
    out <<  " and total: " << SD.getpopUnder5Count();
    out << "\nEducation info: ";
    out << "\n(Bachelor or more): " << SD.getBAup()<<"\%";
    out <<  " and total: " << SD.getBAupCount();
    out << "\n(high school or more): " << SD.getHSup()<<"\%";
    out <<  " and total: " << SD.getHSupCount();
    out << "\npersons below poverty: " << SD.getBelowPoverty()<<"\%";
    out <<  " and total: " << SD.getBelowPovertyCount();  
    out << "\nTotal population: " << SD.getPop();
    out << "\n" << SD.getRaceData();

  
    return out;
}
