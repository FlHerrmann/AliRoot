/**************************************************************************
 * Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 *                                                                        *
 * Author: The ALICE Off-line Project.                                    *
 * Contributors are mentioned in the code where appropriate.              *
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/


//////////////////////////////////////////////////////
//                                                  //
//     Class to specify cuts for track analysis     //
//     with AliTPCcalibTracks                       //
//                                                  //
//////////////////////////////////////////////////////

#include <iostream>
#include <TString.h>
#include <TChain.h>
#include <TList.h>
#include "AliTPCcalibTracksCuts.h"

ClassImp(AliTPCcalibTracksCuts)


AliTPCcalibTracksCuts::AliTPCcalibTracksCuts():
  TNamed("calibTracksCuts", "calibTracksCuts"),
  fMinClusters(0),            // number of clusters
  fMinRatio(0),               // kMinRratio = 0.4
  fMax1pt(0),                 // kMax1pt = 0.5
  fEdgeYXCutNoise(0),         // kEdgeYXCutNoise = 0.13
  fEdgeThetaCutNoise(0),      // kEdgeThetaCutNoise = 0.018
  fOutputFileName()          // filename of outputfile ('Output.root')
{
   // 
   // default constructor
   // 
}


AliTPCcalibTracksCuts::AliTPCcalibTracksCuts(Int_t minClusters, Float_t minRatio, Float_t max1pt,
					     Float_t edgeXZCutNoise, Float_t edgeThetaCutNoise, char* outputFileName):
      TNamed("calibTracksCuts", "calibTracksCuts"),
      fMinClusters(minClusters),            // number of clusters
      fMinRatio(minRatio),                  // kMinRratio = 0.4
      fMax1pt(max1pt),                      // kMax1pt = 0.5
      fEdgeYXCutNoise(edgeXZCutNoise),      // kEdgeYXCutNoise = 0.13
      fEdgeThetaCutNoise(edgeThetaCutNoise),   // kEdgeThetaCutNoise = 0.018
      fOutputFileName()                    // filename of outputfile ('Output.root')
{
   //
   // Constructor for AliTPCcalibTracksCuts
   // specify the cuts to be set on the processed tracks
   // default cuts are for comics
   //
   fOutputFileName = outputFileName;
}

AliTPCcalibTracksCuts::AliTPCcalibTracksCuts(AliTPCcalibTracksCuts *cuts):
  TNamed(cuts->GetName(), cuts->GetTitle()),
  fMinClusters(cuts->GetMinClusters()),             // number of clusters
  fMinRatio(cuts->GetMinRatio()),                   // kMinRratio = 0.4
  fMax1pt( cuts->GetMax1pt()),                      // kMax1pt = 0.5
  fEdgeYXCutNoise(cuts->GetEdgeYXCutNoise()),       // kEdgeYXCutNoise = 0.13
  fEdgeThetaCutNoise( cuts->GetEdgeThetaCutNoise()),   // kEdgeThetaCutNoise = 0.018
  fOutputFileName(0)                                // filename of outputfile ('Output.root')
{
  // 
  // copy constructor
  // 
  fOutputFileName = cuts->GetOutputFileName();
}



AliTPCcalibTracksCuts::~AliTPCcalibTracksCuts(){
  //
  // Destructor
  //
  cout << "AliTPCcalibTracksCuts destructor called, nothing happend." << endl;
}




void AliTPCcalibTracksCuts::AddCuts(TChain * chain, char* ctype, char* outputFileName){
   // 
   // add predefined cuts to the chain for processing
   // (creates AliTPCcalibTracksCuts object)
   // the cuts are set in the following order:
   // fMinClusters (number of clusters)
   // fMinRatio 
   // fMax1pt   1  over p_t
   // fEdgeYXCutNoise
   // fEdgeThetaCutNoise
   // 
   // The following predefined sets of cuts can be selected:
   // laser:      20, 0.4, 0.5, 0.13, 0.018
   // cosmic:     20, 0.4, 0.5, 0.13, 0.018
   // lowflux:    20, 0.4, 5, 0.2, 0.0001
   // highflux:   20, 0.4, 5, 0.2, 0.0001
   // 
   
   TString cutType(ctype);
   cutType.ToUpper();
   AliTPCcalibTracksCuts *cuts = 0;
   if (cutType == "LASER")
//       cuts = new AliTPCcalibTracksCuts(20, 0.4, 0.5, 0.13, 0.018);
      cuts = new AliTPCcalibTracksCuts(20, 0.4, 5, 0.13, 0.018, outputFileName);
   else if (cutType == "COSMIC")
      cuts = new AliTPCcalibTracksCuts(20, 0.4, 0.5, 0.13, 0.018, outputFileName);
   else if (cutType == "LOWFLUX")
      cuts = new AliTPCcalibTracksCuts(20, 0.4, 5, 0.2, 0.0001, outputFileName);
   else if (cutType == "HIGHFLUX")
      cuts = new AliTPCcalibTracksCuts(20, 0.4, 5, 0.2, 0.0001, outputFileName);
   else {
      cuts = new AliTPCcalibTracksCuts(20, 0.4, 5, 0.2, 0.0001, outputFileName);
      cerr << "WARNING! unknown type '" << ctype << "', cuts set to default values for cosmics." << endl;
      cutType = "COSMIC";
   }
   chain->GetUserInfo()->AddLast(cuts);
   cout << "Cuts were set to predefined set: " << cutType << endl;
}

void AliTPCcalibTracksCuts::AddCuts(TChain * chain, Int_t minClusters, Float_t minRatio, Float_t max1pt,
      Float_t edgeXZCutNoise, Float_t edgeThetaCutNoise, char* outputFileName){
   // 
   // add user defined cuts to the chain for processing
   // (creates AliTPCcalibTracksCuts object)
   // the cuts are set in the following order:
   // fMinClusters (number of clusters)
   // fMinRatio 
   // fMax1pt   1  over p_t
   // fEdgeYXCutNoise
   // fEdgeThetaCutNoise
   // 
   chain->GetUserInfo()->AddLast(new AliTPCcalibTracksCuts(minClusters, minRatio, max1pt, edgeXZCutNoise, edgeThetaCutNoise, outputFileName));
   printf("Cuts were set to the individal values: minClusters: %i, minRatio: %f, max1pt: %f, edgeXZCutNoise: %f, edgeThetaCutNoise: %f \n", 
      minClusters, minRatio, max1pt, edgeXZCutNoise, edgeThetaCutNoise);
}

void AliTPCcalibTracksCuts::Print(Option_t* option) const  {
  //
  // Print the cut contents
  //
   option = option;  // to avoid compiler warnings
   cout << "<AliTPCcalibTracksCuts>: The following cuts are specified: " << endl;
   cout << "fMinClusters: " << fMinClusters << endl;
   cout << "fMinRatio: " << fMinRatio << endl;
   cout << "fMax1pt: " << fMax1pt << endl;
   cout << "fEdgeYXCutNoise: " << fEdgeYXCutNoise << endl;
   cout << "fEdgeThetaCutNoise: " << fEdgeThetaCutNoise << endl;
   cout << "fOutputFileName: " << fOutputFileName.GetName() << endl;
}  // Prints out the specified cuts
