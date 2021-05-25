#ifndef VCOMBOC_H
#define VCOMBOC_H

#include "psData.h"
#include "psCombo.h"
#include "demogData.h"
#include "demogCombo.h"
#include "visitorCombine.h"
#include "parse.h"
#include <memory>
#include <fstream>
#include <cassert>

class visitorCombineCounty : public visitorCombine {
public:
    visitorCombineCounty() {
    }

    //store demographic data by county name
	void visit(shared_ptr<demogData> obj) {
        string regionName = obj->getRegionName();
        
            string name = "";
            if (regionName.find("County") != string::npos){
                name = regionName.substr(0,regionName.size()-7) + obj->getState();
                
            }else{
                 name = regionName + obj->getState();
            }
            if (allComboDemogData.count(name) == 0){
                allComboDemogData[name] = make_shared<demogCombo>(obj->getState(), 1, obj->getpopOver65Count(), obj->getpopUnder18Count(),
                                                                        obj->getpopUnder5Count(), obj->getBAupCount(), obj->getHSupCount(), obj->getBelowPovertyCount(), obj->getRaceData(), obj->getPop());
            }else{
                allComboDemogData[name]->add_demogCombo(obj);
            }
       
                
    }
    
    //aggregate police shooting data by county
    void visit(shared_ptr<psData> obj) {
        string regionName = obj->getRegionName();
        
            string name = "";
            if (regionName.find("County") != string::npos){
                name = regionName.substr(0,regionName.size()-7) + obj->getState();
            }else{
                name = regionName + obj->getState();
            }
            if(allComboPoliceData.count(name) == 0){
                allComboPoliceData[name] = make_shared<psCombo>(regionName, obj->getState());
                allComboPoliceData[name]->add_psCombo(obj);       
            }else{
                allComboPoliceData[name]->add_psCombo(obj);
            }
         
    }

    void visit(shared_ptr<psCombo> obj){
        
    }

    private:
        //only inherited data at this point
};

#endif
