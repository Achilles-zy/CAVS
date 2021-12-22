#include "CDEXActionInitialization.hh"
#include "CDEXPrimaryGeneratorAction.hh"
#include "CDEXRunAction.hh"
#include "CDEXRunActionMaster.hh"
#include "CDEXEventAction.hh"
#include "CDEXSteppingAction.hh"
#include "CDEXTrackingAction.hh"
#include "CDEXStackingAction.hh"
#include "G4Threading.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CDEXActionInitialization::CDEXActionInitialization()
	: G4VUserActionInitialization()
{
	
	PList =new CDEXParameterList();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CDEXActionInitialization::~CDEXActionInitialization()
{
	delete PList;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CDEXActionInitialization::BuildForMaster() const
{
	CDEXPrimaryGeneratorAction *fPGA = new CDEXPrimaryGeneratorAction(PList);
	//CDEXRunActionMaster *runActionMaster = new CDEXRunActionMaster(fPrimaryGen, fDetCons);
	//SetUserAction(runActionMaster);
	CDEXRunAction *runAction = new CDEXRunAction(PList);
	SetUserAction(runAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CDEXActionInitialization::Build() const
{
	CDEXPrimaryGeneratorAction *fPGA = new CDEXPrimaryGeneratorAction(PList);
	CDEXRunAction *runAction = new CDEXRunAction(PList);
	//CDEXRunActionMaster *runActionMaster = new CDEXRunActionMaster(fPrimaryGen, fDetCons);

	// if (G4Threading::IsMultithreadedApplication())
	// 	SetUserAction(runAction);
	// else
	// 	SetUserAction(runActionMaster); // Use master version for sequential
	// CDEXRunAction *runAction = new CDEXRunAction(gen, fDetCons);
	// SetUserAction(runAction);

	CDEXEventAction *eventAction = new CDEXEventAction(runAction);

	CDEXTrackingAction *trackAction = new CDEXTrackingAction(eventAction);

	SetUserAction(fPGA);
	SetUserAction(runAction);
	SetUserAction(eventAction);
	SetUserAction(trackAction);
	SetUserAction(new CDEXSteppingAction(trackAction, eventAction, runAction));
	SetUserAction(new CDEXStackingAction);
}