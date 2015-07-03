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

    G4double z[] = {2.0*cm, 12.0*cm, 21.0*cm};

    std::ofstream haloFile("Rbin_fit2.txt");

    haloFile << "z/r ";

    for (G4int i = 0; i <= 100; i++)
    {
        haloFile << i << " ";
    }

    haloFile << "\n";

    for (int j = 0; j < 3; j++)
    {
        haloFile << z[j]/cm << " ";

        for (G4int i = 0; i < 101; i++)
        {
            haloFile << Cells[i][j]*6.24*pow(10,9)/100000 << " ";
        }

        haloFile << "\n";
    }
}

