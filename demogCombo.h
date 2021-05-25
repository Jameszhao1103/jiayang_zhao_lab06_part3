#ifndef COMBODEMOG_H
#define COMBODEMOG_H

#include <memory>
#include <string>
#include <iostream>
#include "demogData.h"
#include "raceDemogData.h"


/*
  class to represent combined demographic data 
*/
class demogCombo : public demogData {
  public:
      demogCombo(string state, int num, int in65, int in18, int in5, int inBA,int inHS,int inPoor,raceDemogData inRace,int Total):
      numberofcounty(num), demogData{state,in65,in18,in5,inBA,inHS,inPoor,inRace,Total} {}

      void setNumberofcounty(int county) { numberofcounty = county; }
      int getNumberofcounty() const      { return numberofcounty; }

      void add_demogCombo(shared_ptr<demogData> data){
        setNumberofcounty(getNumberofcounty() + 1);
        addpopOver65Count(data->getpopOver65Count());
        addpopUnder18Count(data->getpopUnder18Count());
        addpopUnder5Count(data->getpopUnder5Count());
        addpopBACount(data->getBAupCount());
        addpopHSCount(data->getHSupCount());
        addpopPoorCount(data->getBelowPovertyCount());
        addRacedata(data->getRaceData());
        addTotalpop(data->getPop());
      }
      
      


      friend std::ostream &operator<<(std::ostream &out, const demogCombo &SD);

    private:
      int numberofcounty;

};
#endif
