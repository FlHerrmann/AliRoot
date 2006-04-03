#ifndef ALITPCRECONSTRUCTOR_H
#define ALITPCRECONSTRUCTOR_H
/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice                               */

/* $Id$ */

#include "AliReconstructor.h"

class AliTPCParam;


class AliTPCReconstructor: public AliReconstructor {
public:
  AliTPCReconstructor(): AliReconstructor() {};
  virtual ~AliTPCReconstructor() {};

  virtual void         Reconstruct(AliRunLoader* runLoader) const;
  virtual void         Reconstruct(AliRunLoader* runLoader,
				   AliRawReader* rawReader) const;
  virtual void         Reconstruct(TTree* digitsTree, TTree* clustersTree) const {
    AliReconstructor::Reconstruct(digitsTree,clustersTree);
  }
  virtual void         Reconstruct(AliRawReader* rawReader, TTree* clustersTree) const {
    AliReconstructor::Reconstruct(rawReader,clustersTree);
  }
  virtual AliTracker*  CreateTracker(AliRunLoader* runLoader) const;
  virtual void         FillESD(AliRunLoader* runLoader, AliESD* esd) const;
  virtual void         FillESD(TTree* digitsTree, TTree* clustersTree, 
			       AliESD* esd) const {
    AliReconstructor::FillESD(digitsTree,clustersTree,esd);
  }
  virtual void         FillESD(AliRawReader* rawReader, TTree* clustersTree, 
			       AliESD* esd) const {
    AliReconstructor::FillESD(rawReader,clustersTree,esd);
  }
  virtual void         FillESD(AliRunLoader* runLoader, 
			       AliRawReader* rawReader, AliESD* esd) const {
    AliReconstructor::FillESD(runLoader,rawReader,esd);
  }

  static void SetCtgRange(Double_t ctgRange = 1.05) {fgCtgRange = ctgRange;}
  static Double_t GetCtgRange(){ return fgCtgRange;}

  static void SetMaxSnpTracker(Double_t maxSnp) {fgMaxSnpTracker = maxSnp;}
  static Double_t GetMaxSnpTracker(){ return fgMaxSnpTracker;}
  static void SetMaxSnpTrack(Double_t maxSnp) {fgMaxSnpTrack = maxSnp;}
  static Double_t GetMaxSnpTrack(){ return fgMaxSnpTrack;}

  static Int_t StreamLevel()               { return fgStreamLevel;}
  static void  SetStreamLevel(Int_t level) { fgStreamLevel = level;}

private:
  AliTPCParam*         GetTPCParam(AliRunLoader* runLoader) const;

  static Double_t fgCtgRange; //! +-fCtgRange is the ctg(Theta) window used for clusterization and tracking (MI) 
  static Double_t fgMaxSnpTracker;   // max sin of local angle  - for TPC tracker
  static Double_t fgMaxSnpTrack;     // max sin of local angle  - for track 
  static Int_t    fgStreamLevel;     // flag for streaming      - for TPC reconstruction

  ClassDef(AliTPCReconstructor, 0)   // class for the TPC reconstruction
};

#endif
