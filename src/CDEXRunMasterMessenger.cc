#include "CDEXRunMessenger.hh"
#include "CDEXRunMasterMessenger.hh"
#include "CDEXRunActionMaster.hh"
#include "CDEXRunAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithABool.hh"
#include "G4SystemOfUnits.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

class CDEXPrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;
class G4UIcmdWithoutParameter;
class G4UIcmdWithAnInteger;
class G4UIcmdWithABool;


CDEXRunMasterMessenger::CDEXRunMasterMessenger(CDEXRunActionMaster* runmaster)
    : G4UImessenger(),
    cmdSetRefresh(0)
{
    fSrcDir = new G4UIdirectory("/CDEX/run/");
    fSrcDir->SetGuidance("Run control");

    cmdSetRefresh = new G4UIcmdWithABool("/CDEX/run/refresh", this);
	cmdSetRefresh->SetGuidance("Set if to refresh output");
	cmdSetRefresh->SetParameterName("Ifrefresh", false);
	cmdSetRefresh->AvailableForStates(G4State_PreInit, G4State_Idle);
	cmdSetRefresh->SetToBeBroadcasted(false);

    fActionMaster = runmaster;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CDEXRunMasterMessenger::~CDEXRunMasterMessenger()
{
    delete fSrcDir;
    delete cmdSetRefresh;
    //delete fAction;//debug
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CDEXRunMasterMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
    if (command == cmdSetRefresh) {
        fActionMaster->SetRefresh(cmdSetRefresh->GetNewBoolValue(newValue));
	}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
