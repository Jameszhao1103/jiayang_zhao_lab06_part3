#ifndef VCOMBOS_H
#define VCOMBOS_H


#include "visitorCombine.h"
#include <memory>

class visitorCombineState : public visitorCombine {
public:
    visitorCombineState() {}

	void visit(shared_ptr<demogData> obj) {
        string stateName = obj->getState();
        if( allComboDemogData.count(stateName) == 0){
            allComboDemogData[stateName] = make_shared<demogCombo>(obj->getState(), 1, obj->getpopOver65Count(), obj->getpopUnder18Count(),
                                                                    obj->getpopUnder5Count(), obj->getBAupCount(), obj->getHSupCount(), obj->getBelowPovertyCount(), obj->getRaceData(), obj->getPop());
        }else{
            allComboDemogData[stateName]->add_demogCombo(obj);
        }
    }

    
    
    void visit(shared_ptr<psData> obj) {
        string stateName = obj->getState();
        if (allComboPoliceData.count(stateName) == 0){
            allComboPoliceData[stateName] = make_shared<psCombo>(obj->getRegionName(), stateName);
            allComboPoliceData[stateName]->add_psCombo(obj);
            
        }
        else{
            allComboPoliceData[stateName]->add_psCombo(obj);
        }
    }

    void visit(shared_ptr<psCombo> obj){
        
    }
    private:
       //inherited
};

#endif
