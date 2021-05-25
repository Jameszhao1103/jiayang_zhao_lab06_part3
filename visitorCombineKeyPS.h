#ifndef VCOMBOV_H
#define VCOMBOV_H

#include "psData.h"
#include "psCombo.h"
#include "demogData.h"
#include "demogCombo.h"
#include "visitorCombine.h"
#include <memory>


class visitorCombineKeyPS : public visitorCombine {
public:
    visitorCombineKeyPS(string (*psf)(shared_ptr<psData>),std::map<string, string>& mapPSToKey) {
      psfunc = psf;
     
   }

	void visit(shared_ptr<demogData> obj) {

    }
    
    void visit(shared_ptr<psData> obj) {
        //wait to fill in
    }

    void visit(shared_ptr<psCombo> obj){
        
    }

    private:
      //the function pointers to the key functions
      string (*psfunc)(shared_ptr<psData>);
      
};

#endif
