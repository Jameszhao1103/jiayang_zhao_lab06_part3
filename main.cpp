#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "demogData.h"
#include "psData.h"
#include "parse.h"
#include "visitorCombine.h"
#include "statTool.h"
#include "visitor.h"
#include "visitorCreateKey.h"
#include "visitorCombineState.h"
#include "visitorCombineCounty.h"
#include "visitorCombineKeyPS.h"
#include "visitorCombineKeyDemog.h"


using namespace std;

string makeKeyDemog(shared_ptr<demogData> theData) {

  string theKey = "Key";

  if (theData->getCommunityRaceMix().getBlackPercent() > 20) {
    theKey += "AfriAmerTwentyPer";
  } else if (theData->getCommunityRaceMix().getLatinxPercent() > 20) {
    theKey += "LatinxPerTwentyPer";
  } else if (theData->getCommunityRaceMix().getFirstNationPercent() > 20) {
    theKey += "FirstNationTwentyPer";
  } else if (theData->getCommunityRaceMix().getAsianPercent() > 20) {
    theKey += "AsianTwentyPer";
  } else {
    theKey += "Other";
  }

  return theKey;
}

string makeKeyPS(shared_ptr<psData> theData) {

  string theKey = "Key";
  if (theData->getRace() == "W") {
    theKey += "WhiteVictim";
  } else if (theData->getRace() == "A") {
    theKey += "AsianVictim";
  } else if (theData->getRace() == "H") {
    theKey += "HispanicVictim";
  } else if (theData->getRace() == "N") {
    theKey += "NativeAmericanVictim";
  } else if (theData->getRace() == "B") {
    theKey += "AfricanAmericanVictim";
  } else if (theData->getRace() == "O") {
    theKey += "OtherRace";
  } else {
    theKey += "RaceUnspecified";
  }
  return theKey;
}


int main() {
    vector<shared_ptr<regionData>> pileOfData;

    read_csv(pileOfData, "police_shootings_cleaned.csv", POLICE);
    read_csv(pileOfData, "county_demographics.csv", DEMOG);

    visitorCombineState theStates;
    statTool::createStateData(pileOfData, theStates);
    theStates.printAllCombo(&demogData::getBelowPovertyCount, &psCombo::getNumberOfCases);

    visitorCombineCounty theCounties;
    statTool::createCountyData(pileOfData, theCounties);
    theCounties.printAllCombo(&demogData::getBelowPovertyCount, &psCombo::getNumberOfCases);

  //statTool::computeStatsDemogRegionData(&theCounties, &demogData::getpopUnder18,
  //                                      &demogData::getBelowPoverty, &demogData::getpopUnder18Count, &demogData::getBelowPovertyCount);

  //statTool::computeStatsMixRegionData(&theCounties, &demogData::getPop, &psCombo::getNumberOfCases);

  //statTool::computeStatsRaceProportion(&theStates,&raceDemogData::getAsianCount,&raceDemogData::getAsianCount);

    visitorCreateKey theKeys(&makeKeyDemog, &makeKeyPS);
    statTool::createKeys(pileOfData, theKeys);

    visitorCombineKeyDemog theKeyedDemog(&makeKeyDemog, theKeys.getDemogRegionToKey());
    statTool::createKeyedDataDemog(pileOfData, theKeyedDemog);
    theKeyedDemog.printAllCombo();

    visitorCombineKeyPS theKeyedPS(&makeKeyPS, theKeys.getPsRegionToKey());
    statTool::createKeyedDataPS(pileOfData, theKeyedPS);
    theKeyedPS.printAllCombo();

  return 0;
}

