#ifndef DEMOG_H
#define DEMOG_H

#include "raceDemogData.h"
#include "regionData.h"

#include <string>
#include<iostream>
#include <memory>

using namespace std;


class demogData : public regionData, public std::enable_shared_from_this<demogData> {
  public:
      demogData(string inN, string inS, int in65, int in18,int in5, int inBA, int inHS, int inPoor, raceDemogData inrace, int totPop14) :
          regionData(inN,inS,totPop14), popOver65Count(in65), popUnder18Count(in18),
          popUnder5Count(in5), popBACount(inBA), popHSCount(inHS), popPoorCount(inPoor), race(inrace){}

      demogData(string inS, int in65, int in18,int in5, int inBA, int inHS, int inPoor, raceDemogData inrace, int totPop14) :
          regionData(inS,inS,totPop14), popOver65Count(in65), popUnder18Count(in18),
          popUnder5Count(in5), popBACount(inBA), popHSCount(inHS), popPoorCount(inPoor), race(inrace){}
      
    double getpopOver65()       const { return 100.0f*(double)(popOver65Count)/getPop();  }
    double getpopUnder18()      const { return 100.0f*(double)(popUnder18Count)/getPop();  }
    double getpopUnder5()       const { return 100.0f*(double)(popUnder5Count)/getPop(); }
    double getBAup()            const { return 100.0f*(double)(popBACount)/getPop(); }
    double getHSup()            const { return 100.0f*(double)(popHSCount)/getPop();}
    double getBelowPoverty()         const { return 100.0f*(double)(popPoorCount)/getPop(); }

    int getpopOver65Count()  const { return popOver65Count;  }
    int getpopUnder18Count() const { return popUnder18Count;  }
    int getpopUnder5Count()  const { return popUnder5Count;  }
    int getBAupCount()       const { return popBACount; }
    int getHSupCount()       const { return popHSCount;  }
    int getBelowPovertyCount()    const { return popPoorCount;  }
    raceDemogData getRaceData() const { return race; }

    void addpopOver65Count(int in65)   { popOver65Count += in65; }
    void addpopUnder18Count(int in18)  { popUnder18Count += in18; }
    void addpopUnder5Count(int in5)    { popUnder5Count += in5; }
    void addpopBACount(int inBA)       { popBACount+= inBA; }
    void addpopHSCount(int inHS)       { popHSCount+= inHS; }
    void addpopPoorCount(int inPoor)   { popPoorCount+= inPoor; }
    void addRacedata(raceDemogData inRace){ race += inRace; }
    void addTotalpop(int total)           { setPop(getPop() + total); }

    friend std::ostream& operator<<(std::ostream &out, const demogData &DD);

    void accept(class Visitor &v) override;

    raceDemogData getCommunityRaceMix() const { return race; }

    int getWhiteCount() const { return race.getWhiteCount(); }
    int getBlackCount() const { return race.getBlackCount(); }

private:
    int popOver65Count;
    int popUnder18Count;
    int popUnder5Count;
    int popBACount;
    int popHSCount;
    int popPoorCount;
    raceDemogData race;
    
   
};
#endif
