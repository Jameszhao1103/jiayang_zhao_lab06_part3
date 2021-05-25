#ifndef VCOMBOK_H
#define VCOMBOK_H

#include "psData.h"
#include "psCombo.h"
#include "demogData.h"
#include "demogCombo.h"
#include "visitorCombine.h"
#include <memory>


class visitorCombineKeyDemog : public visitorCombine {
public:
    visitorCombineKeyDemog(string (*df)(shared_ptr<demogData>),std::map<string, string>& mapDemogToKey) {
      demogFunc = df;
      
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
      string (*demogFunc)(shared_ptr<demogData>);
      string (*psFunc)(shared_ptr<psData>);
};

#endif
