#ifndef CDEXPrimaryGeneratorAction_h
#define CDEXPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "CDEXDetectorConstruction.hh"
#include "CDEXPrimaryGeneratorMessenger.hh"
#include "G4GeneralParticleSource.hh"
#include "CDEXParameterList.hh"
#include "CDEXRunAction.hh"
class G4GeneralParticleSource;
class G4Event;
class CDEXDetectorConstruction;
class CDEXPrimaryGeneratorMessenger;
class CDEXParameterList;

class CDEXPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
    CDEXPrimaryGeneratorAction(CDEXParameterList*);
    ~CDEXPrimaryGeneratorAction();
    void GeneratePrimaries(G4Event *anEvent);
    G4double GetPrimaryE() const
    {
        return fPrimaryE;
    }

    G4String GetPrimaryName() const
    {
        return fPrimaryName;
    }

    G4double GetBeamTheta() const
    {
        return fBeamTheta;
    }

    G4double GetBeamPhi() const
    {
        return fBeamPhi;
    }

    G4double GetWavelength() const
    {
        return fWavelength;
    }

    void SetSrcType(G4String type)
    {
        fSrcType = type;
    }

    void SetBeamTheta(G4double theta)
    {
        fBeamTheta = theta;
    }

    void SetBeamPhi(G4double phi)
    {
        fBeamPhi = phi;
    }

    void SetWavelength(G4double wavelength)
    {
        fWavelength = wavelength;
    }

    void ResetGPS(){
        fCDEXGPS->ClearAll();
    }

    G4String GetSrcType() const
    {
        return fSrcType;
    }

private:
    G4double fPrimaryE;
    G4double fInitialE;
    G4String fPrimaryName;
    G4String fSrcType;

    G4double fBeamPhi;
    G4double fBeamTheta;
    G4double fWavelength;

    G4int ImprintID=1;

    G4GeneralParticleSource *fCDEXGPS;
    CDEXPrimaryGeneratorMessenger *fPrimaryMessenger;
    CDEXParameterList* PList;
};

#endif