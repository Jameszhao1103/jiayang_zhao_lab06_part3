#ifndef VCOMBOKD_H
#define VCOMBOKD_H

#include "psData.h"
#include "psCombo.h"
#include "demogData.h"
#include "demogCombo.h"
#include "visitorCombine.h"
#include "visitorCreateKey.h"
#include <memory>
#include <algorithm>

class visitorCombineKeyDemog : public visitorCombine
{
public:
  visitorCombineKeyDemog(string (*df)(shared_ptr<demogData>), std::map<string, string> mapDemogToKey)
  {
    demogFunc = df;
    assert(mapDemogToKey.size() > 0);
    mapDemogKey = mapDemogToKey;
  }

  //just store based on function
  void visit(shared_ptr<demogData> obj)
  {
    string keyName = (*demogFunc)(obj);
    if (allComboDemogData.count(keyName) == 0)
    {
      allComboDemogData[keyName] = make_shared<demogCombo>(obj->getState(), 1, obj->getpopOver65Count(), obj->getpopUnder18Count(),
                                                           obj->getpopUnder5Count(), obj->getBAupCount(), obj->getHSupCount(),
                                                           obj->getBelowPovertyCount(), obj->getCommunityRaceMix(), obj->getPop());
    }
    else
    {
      allComboDemogData[keyName]->add_demogCombo(obj);
      allComboDemogData[keyName]->addState(obj->getState());
    }
  }
  void visit(shared_ptr<psCombo> obj)
    {
        std::cout << "";
    }
  //store based on demog key
  void visit(shared_ptr<psData> obj)
  {
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
    string keyName = mapDemogKey[key];
    psCombo s(regionName, obj->getState());
    s.add_psCombo(obj);
    if (allComboPoliceData.count(keyName) == 0)
    {
      allComboPoliceData[keyName] = make_shared<psCombo>(regionName, obj->getState());
      *allComboPoliceData[keyName] += s;
    }
    else
    {
      *allComboPoliceData[keyName] += s;
      allComboPoliceData[keyName]->addState(obj->getState());
    }
  }
    void printAllCombo(){
      vector<string> things;
      for (auto obj : mapDemogKey)
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
  string (*demogFunc)(shared_ptr<demogData>);
  std::map<string, string> mapDemogKey;
  //want a way to keep region to key for mapping between the two dataTypes
};

#endif