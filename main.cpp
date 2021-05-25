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

#include "visitorCombineState.h"
#include "visitorCombineCounty.h"
#include "visitorCombineKeyPS.h"
#include "visitorCombineKeyDemog.h"

using namespace std;
//README: This is a paired lab. The memebers are Jiayang Zhao and Ziyue Wang.
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

  statTool::computeStatsMixRegionData(&theCounties, &demogData::getPop, &psCombo::getNumberOfCases);

  //statTool::computeStatsRaceProportion(&theStates,&raceDemogData::getAsianCount,&raceDemogData::getAsianCount);

  

  return 0;
}

