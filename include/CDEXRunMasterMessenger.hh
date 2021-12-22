#pragma once
#ifndef CDEXRunMasterMessenger_h
#define CDEXRunMasterMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class CDEXRunAction;
class CDEXRunActionMaster;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;
class G4UIcmdWithoutParameter;
class G4UIcmdWithAnInteger;
class G4UIcmdWithABool;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class CDEXRunMasterMessenger : public G4UImessenger
{
public:
    CDEXRunMasterMessenger(CDEXRunActionMaster*);
    virtual ~CDEXRunMasterMessenger();

    virtual void SetNewValue(G4UIcommand*, G4String);

private:
    CDEXRunActionMaster* fActionMaster;
    G4UIdirectory* fSrcDir;
    G4UIcmdWithABool* cmdSetRefresh;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
