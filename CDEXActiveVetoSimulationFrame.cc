#include "CDEXDetectorConstruction.hh"
#include "CDEXPhysicsList.hh"
#include "CDEXRunAction.hh"
#include "CDEXEventAction.hh"
#include "CDEXTrackingAction.hh"
#include "CDEXSteppingAction.hh"
#include "CDEXActionInitialization.hh"
#include "CDEXPrimaryGeneratorAction.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4OpticalPhysics.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

// #define G4MT_USE

// #ifdef G4MT_USE
// #include "G4MTRunManager.hh"
// #else
// #include "G4RunManager.hh"
// #endif
#include "G4UImanager.hh"
#include "time.h"

//#define G4VIS_USE
//#define G4UI_USE

//#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
//#endif

//#ifdef G4UI_USE
#include "G4UIExecutive.hh"
//#endif

#include "Randomize.hh"
#include "CDEXMaterials.hh"
#include "QBBC.hh"
#include "Shielding.hh"
#include <G4VUIshell.hh>

#include "G4MPImanager.hh"
#include "G4MPIsession.hh"


int main(int argc, char **argv)
{
    // Choose the Random engine
    G4Random::setTheEngine(new CLHEP::RanecuEngine);
    G4long seed = time(NULL);
    G4Random::setTheSeed(seed);



    // --------------------------------------------------------------------
    // MPI session
    // --------------------------------------------------------------------
    // At first, G4MPImanager/G4MPIsession should be created.
    G4MPImanager *g4MPI = new G4MPImanager(argc, argv);

    // MPI session (G4MPIsession) instead of G4UIterminal
    // Terminal availability depends on your MPI implementation.
    G4MPIsession *session = g4MPI->GetMPIsession();

    // LAM/MPI users can use G4tcsh.
    // G4String prompt = "[40;01;33m";
    // prompt += "G4MPI";
    // prompt += "[40;31m(%s)[40;36m[%/][00;30m:";
    // session->SetPrompt(prompt);

#ifdef G4MULTITHREADED
    G4MTRunManager *CDEXRunManager = new G4MTRunManager;
#else
    G4RunManager *CDEXRunManager = new G4RunManager;
#endif
    //CDEXRunManager->GetUserPrimaryGeneratorAction

    CDEXDetectorConstruction *CDEXDetCons = new CDEXDetectorConstruction();
    CDEXRunManager->SetUserInitialization(CDEXDetCons);

    G4PhysicalVolumeStore *PVStore = G4PhysicalVolumeStore::GetInstance();
    G4int i = 0;
    G4VPhysicalVolume *tempPV = NULL;
    while (i < G4int(PVStore->size()))
    {
        tempPV = (*PVStore)[i];
        G4cout << i << " "
               << " " << tempPV->GetName() << " " << G4endl;
        i++;
    }

    G4LogicalVolumeStore *LVStore = G4LogicalVolumeStore::GetInstance();
    i = 0;
    G4LogicalVolume *tempLV = NULL;
    while (i < G4int(PVStore->size()))
    {
        tempLV = (*LVStore)[i];
        G4cout << i << " "
               << " " << tempLV->GetName() << " " << G4endl;
        i++;
    }

    // Physics list
    auto physicslist = new CDEXPhysicsList();
    G4VModularPhysicsList *qbbc = new QBBC;
    G4VModularPhysicsList *shielding = new Shielding;
    physicslist->SetVerboseLevel(0);
    CDEXRunManager->SetVerboseLevel(1);
    CDEXRunManager->SetUserInitialization(physicslist);
    // shielding->RegisterPhysics(new G4OpticalPhysics());
    // CDEXRunManager->SetUserInitialization(shielding);

    CDEXRunManager->SetUserInitialization(new CDEXActionInitialization());

    G4UIExecutive *ui = 0;
    if (argc == 1)
    {
        ui = new G4UIExecutive(argc, argv);
    }
    
    G4VisManager *CDEXVis = new G4VisExecutive;
    CDEXVis->Initialize();

    G4UImanager *UImanager = G4UImanager::GetUIpointer();
    UImanager->ApplyCommand("/control/macroPath /home/yueq/WORK/zhangzy/CDEXSimulationFrame:./:../");

    // --------------------------------------------------------------------
    // ready for go
    // MPIsession treats both interactive and batch modes.
    // Just start your session as below.
    // --------------------------------------------------------------------

    // CDEXRunManager->Initialize();
    // session->SessionStart();

    if (!ui)
    {
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
        // CDEXRunManager->Initialize();
        // session-> SessionStart();
    }
    else
    {
        UImanager->ApplyCommand("/control/execute init_vis.mac");
        ui->SessionStart();
        delete ui;
    }

    // --------------------------------------------------------------------
    // termination
    // --------------------------------------------------------------------

    delete CDEXVis;
    // delete g4MPI;
    delete CDEXRunManager;
}

/// @file exMPI03.cc
//
/// @brief A MPI example code
/*
#include "G4MPImanager.hh"
#include "G4MPIsession.hh"

#include "CDEXDetectorConstruction.hh"
#include "CDEXPhysicsList.hh"
#include "CDEXRunAction.hh"
#include "CDEXEventAction.hh"
#include "CDEXTrackingAction.hh"
#include "CDEXSteppingAction.hh"
#include "CDEXActionInitialization.hh"
#include "CDEXPrimaryGeneratorAction.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4OpticalPhysics.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif
#include <G4VUIshell.hh>
#include "G4UImanager.hh"

#include "G4VisExecutive.hh"

#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"
#include "FTFP_BERT.hh"
#include "G4ScoringManager.hh"
int main(int argc, char** argv)
{
  // --------------------------------------------------------------------
  // MPI session
  // --------------------------------------------------------------------
  // At first, G4MPImanager/G4MPIsession should be created.
  G4MPImanager* g4MPI = new G4MPImanager(argc, argv);

  // MPI session (G4MPIsession) instead of G4UIterminal
  // Terminal availability depends on your MPI implementation.
  G4MPIsession* session = g4MPI-> GetMPIsession();

  // LAM/MPI users can use G4tcsh.
  G4String prompt = "[40;01;33m";
  prompt += "G4MPI";
  prompt += "[40;31m(%s)[40;36m[%/][00;30m:";
  session-> SetPrompt(prompt);

  // --------------------------------------------------------------------
  // user application setting
  // --------------------------------------------------------------------
#ifdef G4MULTITHREADED
  G4MTRunManager* runManager = new G4MTRunManager();
  runManager-> SetNumberOfThreads(4);
#else
  G4RunManager* runManager = new G4RunManager();
#endif
G4ScoringManager * scManager = G4ScoringManager::GetScoringManager();
 scManager->SetVerboseLevel(1);
  // setup your application
  runManager-> SetUserInitialization(new DetectorConstruction);
  runManager-> SetUserInitialization(new FTFP_BERT);
  runManager-> SetUserInitialization(new ActionInitialization);

  runManager-> Initialize();

  G4VisExecutive* visManager = new G4VisExecutive;
  visManager-> Initialize();
  G4cout << G4endl;

  // --------------------------------------------------------------------
  // ready for go
  // MPIsession treats both interactive and batch modes.
  // Just start your session as below.
  // --------------------------------------------------------------------
  session-> SessionStart();
  // G4UImanager *UImanager = G4UImanager::GetUIpointer();
  //   if (argc != 1)
  //   {
  //       G4String command = "/control/execute ";
  //       G4String fileName = argv[1];
  //       UImanager->ApplyCommand(command + fileName);
  //   }
  // --------------------------------------------------------------------
  // termination
  // --------------------------------------------------------------------
  delete visManager;

  delete g4MPI;

  delete runManager;

  return EXIT_SUCCESS;
}
*/