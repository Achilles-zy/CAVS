#pragma once
#ifndef CDEXParameterList_h
#define CDEXParameterList_h 1
//#include "CDEXPrimaryGeneratorAction.hh"
#//include "CDEXRunAction.hh"
#include "globals.hh"

class CDEXParameterList
{
public:
    CDEXParameterList();
    ~CDEXParameterList();
    G4String SrcType;
    G4String PrimaryName;
    G4double PrimaryEnergy;
    //CDEXPrimaryGeneratorAction *PGA;

    void SetSrcType(G4String type)
    {
        SrcType = type;
    }
    G4String GetSrcType() const
    {
        return SrcType;
    }

    void SetPrimaryName(G4String name)
    {
        PrimaryName = name;
    }
    G4String GetPrimaryName() const
    {
        return PrimaryName;
    }

    void SetPrimaryEnergy(G4double e)
    {
        PrimaryEnergy = e;
    }
    G4double GetPrimaryEnergy() const
    {
        return PrimaryEnergy;
    }



private:

};

#endif