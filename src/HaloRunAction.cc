#include "HaloRunAction.hh"
#include "HaloRun.hh"
#include "HaloDetectorHit.hh"

#include "G4RunManager.hh"
#include "HaloDetectorConstruction.hh"
#include "G4THitsMap.hh"
#include "G4SDManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4Run.hh"

#include <fstream>
#define _USE_MATH_DEFINES

HaloRunAction::HaloRunAction(const G4String detectorName) : G4UserRunAction()
{
    DetectorName = detectorName;
}

HaloRunAction::~HaloRunAction()
{}

G4Run* HaloRunAction::GenerateRun()
{
    return new HaloRun(DetectorName, 0);
}

void HaloRunAction::BeginOfRunAction(const G4Run* aRun)
{
    G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;
}

void HaloRunAction::EndOfRunAction(const G4Run* aRun)
{
    if(!IsMaster()) return;

    HaloRun *haloRun = (HaloRun*)aRun;
    Cells = haloRun->GetCells();

    std::ofstream haloFile("Halo_QGSP_BIC_HP.txt");

    for (G4int i = 0; i < 11; i++)
    {
        haloFile << "\n";
        for (int j = 0; j < 70; j++)
            haloFile << i << " " << j*0.375628575 << " " << Cells[i][j]*6.24*pow(10,9)/10000000 << "\n";
    }
}
