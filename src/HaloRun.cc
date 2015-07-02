#include "HaloRun.hh"
#include "G4SDManager.hh"
#include "G4THitsMap.hh"

HaloRun::HaloRun(const G4String detectorName, G4bool verbose) : G4Run()
{
    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    G4VSensitiveDetector* detector = SDman->FindSensitiveDetector(detectorName);

    CollName = detector->GetCollectionName(0);
    CollectionID = SDman->GetCollectionID(CollName);
    Verbose = verbose;

    Cells = new G4double*[11];
    for (int i = 0; i < 11; i++)
    {
        Cells[i] = new G4double[250];
        for (int j = 0; j < 250; j++)
            Cells[i][j] = 0;
    }
}

HaloRun::~HaloRun() {}

void HaloRun::RecordEvent(const G4Event* aEvent)
{
    numberOfEvent++;

    G4HCofThisEvent* HCE = aEvent->GetHCofThisEvent();
    if(HCE!=NULL)
    {
        G4THitsMap<G4double>* HC = static_cast<G4THitsMap<G4double>*>(HCE -> GetHC(CollectionID));
        G4int i = 0;
        G4int j = 0;
        if(HC!=NULL)
        {
            std::map<G4int, G4double*>::iterator it;
            for ( it = HC->GetMap()->begin(); it != HC->GetMap()->end(); it++)
            {
                i = (it->first)/250;
                j = (it->first)%250;
                Cells[i][j] += (*(it->second))/CLHEP::gray;
            }
        }
    }
}

void HaloRun::Merge(const G4Run * aRun)
{
    const HaloRun *localRun = static_cast<const HaloRun*>(aRun);

    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 250; j++)
            Cells[i][j] += localRun->Cells[i][j];
    }

    G4Run::Merge(aRun);
}


