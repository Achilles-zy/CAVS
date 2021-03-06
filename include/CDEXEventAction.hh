#ifndef CDEXEventAction_h
#define CDEXEventAction_h 1

#include "G4UserEventAction.hh"
#include "CDEXRunAction.hh"
#include "globals.hh"
//#include "TROOT.h"
//#include "TFile.h"
//#include "TNtuple.h"
//#include "Rtypes.h"

class TNtuple;
class TFile;
class G4Event;

class CDEXEventAction : public G4UserEventAction
{
public:
  CDEXEventAction(CDEXRunAction *runaction);
  ~CDEXEventAction();

public:
  void BeginOfEventAction(const G4Event *);
  void EndOfEventAction(const G4Event *);
  void AddBulkEnergy(G4double E);
  void AddBulkEnergyDet(G4double E,G4int DetID);
  void AddBulkEnergyString(G4double E,G4int StringID);
  void SiPMTrue() { ifSiPM = true; }
  void DetectableTrue() { ifDetectable = true; }
  void CountTotalSiPMPhoton(G4int ph) { TotalSiPMPhotonCount = TotalSiPMPhotonCount + ph; }
  G4int GetTotalSiPMPhotonCnt() { return TotalSiPMPhotonCount; }
  G4int GetEventID() { return fEventID; }
  G4int GetSiPMSignalCnt(){return SiPMSignalCnt;}
  G4int GetSignalSiPMCount(){return SignalSiPMCount;}
  void CountSiPMSignal() { SiPMSignalCnt += 1; }
  void CountSignalSiPM(G4int SiPMType,G4int SiPMID);
  void AddToSiPM(G4int, G4int);
  void AddToSiPMSignal(G4int, G4int);
  G4int GetSiPMPhotonCount(G4int j, G4int k) { return SiPMPhotonCount[j][k]; }
  G4int GetSiPMSignalCount(G4int j, G4int k) { return SiPMSignalCount[j][k]; }
  G4double GetDistance(G4double x0, G4double y0, G4double z0, G4double x1, G4double y1, G4double z1);

  void RecordStepInfoInScintillator(G4int particletype, G4int creatorprocess, G4double posx, G4double posy, G4double posz, G4double edep);
  void RecordEdepInfoInScintillator(G4int particletype, G4int creatorprocess, G4double posx, G4double posy, G4double posz, G4double edep);
  G4bool IfMultiSiteEvent(std::vector<std::vector<G4double>> edepinfo,G4double distcut,G4double Ecut);
  G4bool IfInterDet(G4double Ecut,G4double EdepList[]);

  void RecordBulkEdep(G4double x,G4double y,G4double z,G4double e){
      std::vector<G4double> OneEdepInfo;
      OneEdepInfo.push_back(x);
      OneEdepInfo.push_back(y);
      OneEdepInfo.push_back(z);
      OneEdepInfo.push_back(e); 
      BulkEdepInfo.push_back(OneEdepInfo);
  }
  void GetEdepStatus();

  
private:
  G4double EdepBulk;
  G4double EdepBulkString[STRINGNUMBER+1];
  G4double EdepBulkDet[DETNUMBER+1];
  G4int SiPMPhotonCount[500][5];
  G4int SiPMSignalCount[500][5];
  G4int RowNb;
  G4int ColumnNb;
  G4int SignalSiPMCount;
  G4int MinSignalSiPMCount;
  G4int SiPMSignalCnt;

  G4int Total;
  G4int DepositeID;

  G4int ID;
  G4int fEventID;
  G4int TotalSiPMPhotonCount;
  G4int DetNumber;
  G4double EnergyThreshold;

  G4int SiPMVetoThreshold;
  G4int SiPMVetoThreshold1;
  G4int SiPMVetoThreshold2;
  G4int SiPMVetoThreshold3;
  G4int SiPMVetoThreshold4;
  G4bool ifBulk;
  G4bool ifROI;
  G4bool ifSiPM;
  G4bool ifFiber;
  G4bool ifDetectable;

  std::vector<std::vector<G4double>> DepositeInfoInScintillator;
  std::vector<std::vector<G4double>> EdepInfoInScintillator;

  std::vector<std::vector<G4double>> TempPosList;
  std::vector<std::vector<G4double>> TempPosListInScintillator;

  std::vector<std::vector<G4int>> TempSiPMList;
  std::vector<std::vector<G4double>> BulkEdepInfo;

  CDEXRunAction *run;

};

#endif