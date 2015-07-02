#include "HaloRunAction.hh"
#include "HaloRun.hh"

#include "G4RunManager.hh"
#include "HaloDetectorConstruction.hh"
#include "G4THitsMap.hh"
#include "G4SDManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4Run.hh"
#include "G4HadronicInteraction.hh"
#include "G4HadronicInteractionRegistry.hh"
#include "G4CascadeInterface.hh"
#include "G4BinaryCascade.hh"
#include "G4AblaInterface.hh"
#include "G4INCLXXInterface.hh"
#include "G4INCLXXInterfaceStore.hh"
#include "G4FermiBreakUp.hh"
#include "G4NistManager.hh"
#include "G4Evaporation.hh"

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
    std::vector<G4HadronicInteraction *> interactions = G4HadronicInteractionRegistry::Instance()->FindAllModels("Binary Cascade");
    for(std::vector<G4HadronicInteraction *>::const_iterator iInter=interactions.begin(), e=interactions.end(); iInter!=e; ++iInter) {
        G4BinaryCascade *theBICInterface = static_cast<G4BinaryCascade*>(*iInter);
        if(theBICInterface)
        {
            G4HadronicInteraction *interaction = G4HadronicInteractionRegistry::Instance()->FindModel("PRECO");
            G4PreCompoundModel *preco = static_cast<G4PreCompoundModel*>(interaction);
            if(!preco)
                preco = new G4PreCompoundModel;
            G4cout << "Tuning Preco" << G4endl;
//            preco->UseHETCEmission();
//            preco->UseSICB();
            preco->GetExcitationHandler()->SetMaxZForFermiBreakUp(10);
            preco->GetExcitationHandler()->SetMaxAForFermiBreakUp(18);
//            G4Evaporation *evaporation = static_cast<G4Evaporation*>(preco->GetExcitationHandler()->GetEvaporation());
//            evaporation->SetGEMChannel();
            theBICInterface->SetDeExcitation(preco);
        }
    }
}

void HaloRunAction::EndOfRunAction(const G4Run* aRun)
{
    if(!IsMaster()) return;

    HaloRun *haloRun = (HaloRun*)aRun;
    Cells = haloRun->GetCells();

    std::ofstream haloFile("adjust.txt");

    haloFile << "z/r 0.0 1.0 2.0 3.0 4.0 5.0 6.0 7.0 8.0 9.0 10.0 \n";
    for (int j = 0; j < 250; j++)
    {
        haloFile << (G4double)(j/10.0) << " ";

        for (G4int i = 0; i < 11; i++)
        {
            haloFile << Cells[i][j]*6.24*pow(10,9)/10000000 << " ";
        }

        haloFile << "\n";
    }
}

