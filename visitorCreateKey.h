#ifndef VISITORCREATEKEY_H
#define VISITORCREATEKEY_H

#include "psData.h"
#include "psCombo.h"
#include "demogData.h"
#include "demogCombo.h"
#include "visitorCombine.h"
#include <memory>

class visitorCreateKey : public Visitor {
public:
    //constructor expects function pointers to the key functions
    visitorCreateKey(string (*df)(shared_ptr<demogData>), string (*psf)(shared_ptr<psData>)){
        
    }
};

#endif