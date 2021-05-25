#ifndef POLICECOMBODATA_H
#define POLICECOMBODATA_H

#include <cassert>
#include <memory>
#include "raceDemogData.h"
#include "psData.h"
#include "regionData.h"


using namespace std;

class psCombo : public regionData, public std::enable_shared_from_this<psCombo>{
public:
    psCombo(string inR,string inS) : regionData(inR,inS), NumberOfCases(0),
     numFemales(0),numMales(0),CasesUnder18(0), CasesOver65(0),FleeingCount(0), NumMentalI(0),RacialData() {}
     
    psCombo(string inS, int inM, int inF, int inO, int inU, raceDemogData inR, int inMale, int inFemale, int intotal) : 
        regionData{inS,inS}, NumMentalI(inM), FleeingCount(inF), CasesOver65(inO), CasesUnder18(inU), RacialData(inR), 
        numMales(inMale), numFemales(inFemale), NumberOfCases(intotal){}
    
    
    int getNumMentalI()     const { return NumMentalI; }
    int getFleeingCount()   const { return FleeingCount; }
    int getCasesOver65()    const { return CasesOver65; }
    int getCasesUnder18()   const { return CasesUnder18; }
    raceDemogData getRacialData() const { return RacialData; }
    int getnumMales()       const { return numMales;  }
    int getnumFemales()     const { return numFemales; }
    int getNumberOfCases()  const { return NumberOfCases; }

    void setRacialData(raceDemogData racial) { RacialData = racial; }

    friend std::ostream& operator<<(std::ostream &out, const psCombo& PD);

    psCombo& operator+=(psCombo &a){
        NumMentalI+=a.NumMentalI;
        FleeingCount+=a.FleeingCount;
        CasesUnder18+=a.CasesUnder18;
        CasesOver65+=a.CasesOver65;
        numFemales+=a.numFemales;
        numMales+=a.numMales;
        NumberOfCases+=a.NumberOfCases;
        RacialData+=a.RacialData;
        return *this;
    }
    void add_psCombo(shared_ptr<psData> obj){
        NumberOfCases++;
        if(obj->getGender()=="M") numMales++;
        else{numFemales++;}
        if(obj->getAge() >= 65) {CasesOver65++;}
        if(obj->getAge() <= 18) {CasesUnder18++;}
        if(obj->getFleeing() != "Not fleeing"&&obj->getFleeing() != ""){FleeingCount++;}
        if(obj->getMentalI() == true) {NumMentalI++;}
        if(obj->getRace() == "N"){
            RacialData.addFirstNationCount(1);
            RacialData.addCommunityCount(1);
        }else  if(obj->getRace() == "A"){
            RacialData.addAsianCount(1);
            RacialData.addCommunityCount(1);
        } else  if(obj->getRace() == "B"){
            RacialData.addBlackCount(1);
            RacialData.addCommunityCount(1);
        } else  if(obj->getRace() == "W"){
            RacialData.addWhiteCount(1);
            RacialData.addCommunityCount(1);
        } else  if(obj->getRace() == "L"){
            RacialData.addLatinxCount(1);
            RacialData.addCommunityCount(1);
        } else  if(obj->getRace() == "H"){
            RacialData.addHIPacificIsleCount(1);
            RacialData.addCommunityCount(1);
        } else  if(obj->getRace() == "O"){
            RacialData.addOtherCount(1);
            RacialData.addCommunityCount(1);
        }else  if(obj->getRace() == "M"){ 
            RacialData.addMultiRaceCount(1);
            RacialData.addCommunityCount(1);
        }
    }

     void accept(class Visitor &v) override;

protected:
    int NumMentalI;
    int FleeingCount;
    int CasesOver65;
    int CasesUnder18;
    raceDemogData RacialData;
    int numMales;
    int numFemales;
    int NumberOfCases;
};

#endif