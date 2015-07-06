//#undef G4MULTITHREADED

#undef G4VIS_USE
#undef G4UI_USE

#include <cstdio>
#include <ctime>

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#include "G4UImanager.hh"
#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#include "HaloPhysicsList.hh"
#include "HaloDetectorConstruction.hh"
#include "HaloPrimaryGeneratorAction.hh"
#include "HaloRunAction.hh"
#include "HaloParallelWorld.hh"
#include "HaloActionInitialization.hh"
#include "G4ComponentBarNucleonNucleusXsc.hh"
#include "G4ComponentGGHadronNucleusXsc.hh"
#include "G4ComponentSAIDTotalXS.hh"
#include "G4BGGNucleonInelasticXS.hh"
#include "G4PreCompoundProton.hh"

int main(int argc,char** argv)
{
    // Set the custom seed for the random engine
    G4Random::setTheEngine(new CLHEP::RanecuEngine);
    G4long seed = time(NULL);
    G4Random::setTheSeed(seed);

#ifdef G4MULTITHREADED
    G4MTRunManager* runManager = new G4MTRunManager;
    runManager->SetNumberOfThreads(8);
#else
    G4RunManager* runManager = new G4RunManager;
#endif

    HaloDetectorConstruction* massWorld = new HaloDetectorConstruction;
    massWorld->RegisterParallelWorld(new HaloParallelWorld("HaloParallelWorld"));

    runManager->SetUserInitialization(massWorld);

    G4VModularPhysicsList* physicsList = new HaloPhysicsList;
    physicsList->SetVerboseLevel(0);
    runManager->SetUserInitialization(physicsList);
    runManager->SetUserInitialization(new HaloActionInitialization);
    runManager->Initialize();

#ifdef G4UI_USE
    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    G4UIExecutive* ui = new G4UIExecutive(argc, argv);
#ifdef G4VIS_USE
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();
    UImanager->ApplyCommand("/control/execute init_vis.mac");
#endif
    ui->SessionStart();
    delete ui;
#else
    runManager->BeamOn(100000000);
#endif

    delete runManager;
    return 0;
}


