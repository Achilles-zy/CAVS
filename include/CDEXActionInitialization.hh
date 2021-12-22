#ifndef CDEXActionInitialization_h
#define CDEXActionInitialization_h 1

#include "G4VUserActionInitialization.hh"
//#include "CDEXPrimaryGeneratorAction.hh"
#include "CDEXDetectorConstruction.hh"
#include "CDEXParameterList.hh"

//class CDEXPrimaryGeneratorAction;
class CDEXDetectorConstruction;
class CDEXParameterList;
/// Action initialization class.

class CDEXActionInitialization : public G4VUserActionInitialization
{
public:
	CDEXActionInitialization();
	virtual ~CDEXActionInitialization();

	virtual void BuildForMaster() const;
	virtual void Build() const;

private:
	CDEXParameterList* PList;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif