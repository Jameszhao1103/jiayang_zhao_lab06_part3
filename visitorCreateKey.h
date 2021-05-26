#ifndef VCOMBOK_H
#define VCOMBOK_H

#include "psData.h"
#include "psCombo.h"
#include "demogData.h"
#include "demogCombo.h"
#include "visitorCombine.h"
#include <memory>

class visitorCreateKey : public Visitor
{
public:
  visitorCreateKey(string (*df)(shared_ptr<demogData>), string (*psf)(shared_ptr<psData>))
  {
    demogFunc = df;
    psFunc = psf;
  }

  void visit(shared_ptr<demogData> obj)
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
    if (mapDemogToKey.count(key) == 0)
    {
      string keyName = (*demogFunc)(obj);
      mapDemogToKey[key] = keyName;
    }
  }
  void visit(shared_ptr<psCombo> obj)
    {
        std::cout << "";
    }
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

    psCombo s(regionName, obj->getState());
    s.add_psCombo(obj);
    if (mapPSToKey.count(key) == 0)
    {
      mapPSToKey[key] = (*psFunc)(obj);
    }
  }
    //add getters as needed
    std::map<string, string> getDemogRegionToKey() { return mapDemogToKey; }
    std::map<string, string> getPsRegionToKey() { return mapPSToKey; }

  private:
    //the function pointers to the key functions
    string (*demogFunc)(shared_ptr<demogData>);
    string (*psFunc)(shared_ptr<psData>);
    std::map<string, string> mapDemogToKey;
    std::map<string, string> mapPSToKey;
    //ADD data to map between location and key
  };

#endif