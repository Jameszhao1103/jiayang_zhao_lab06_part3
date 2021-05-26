#ifndef VCOMBOKP_H
#define VCOMBOKP_H

#include "psData.h"
#include "psCombo.h"
#include "demogData.h"
#include "demogCombo.h"
#include "visitorCombine.h"
#include <memory>
#include <algorithm>


class visitorCombineKeyPS : public visitorCombine {
public:
    visitorCombineKeyPS(string (*psf)(shared_ptr<psData>), std::map<string, string> mapPSToKey) {
      psFunc = psf;
      assert(mapPSToKey.size() > 0);
      mapPSKey = mapPSToKey;
   }

  //based on stored key
	void visit(shared_ptr<demogData> obj) {
   string regionName = obj->getRegionName();
    string key = "";
    if (regionName.find("County") != string::npos)
    {
      key = regionName.substr(0, regionName.size() - 7) + obj->getState();
    }
    else
    {
      key = regionName + obj->getState();
    }
    string keyName = mapPSKey[key];
     if (allComboDemogData.count(keyName) == 0)
    {
      allComboDemogData[keyName] = make_shared<demogCombo>(obj->getState(), 1, obj->getpopOver65Count(), obj->getpopUnder18Count(),
                                                           obj->getpopUnder5Count(), obj->getBAupCount(), obj->getHSupCount(),
                                                           obj->getBelowPovertyCount(), obj->getCommunityRaceMix(), obj->getPop());
    }
    else
    {
      allComboDemogData[keyName]->add_demogCombo(obj);
    }
      
  }
    
  //store based on function
  void visit(shared_ptr<psData> obj) {
    string keyName = (*psFunc)(obj);
    psCombo s(obj->getRegionName(), obj->getState());
    s.add_psCombo(obj);
    if (allComboPoliceData.count(keyName) == 0)
    {
      allComboPoliceData[keyName] = make_shared<psCombo>(obj->getRegionName(), obj->getState());
      *allComboPoliceData[keyName] += s;
    }
    else
    {
      *allComboPoliceData[keyName] += s;
    }
  }
    void visit(shared_ptr<psCombo> obj)
    {
        std::cout << "";
    }

 void printAllCombo(){
      vector<string> things;
      for (auto obj : mapPSKey)
      {
        if(obj.second==""){
          continue;
        }
        if (find(things.begin(), things.end(), obj.second) == things.end()){
          things.push_back(obj.second);
          cout << "name: " << obj.second << endl;
          cout << *allComboDemogData[obj.second] << endl;
          cout << *allComboPoliceData[obj.second] << endl;
        }
      }
    }



  private:
    //the function pointers to the key functions
    string (*psFunc)(shared_ptr<psData>);
    std::map<string, string> mapPSKey;
    //data to help region to key for mapping between the two dataTypes

};

#endif