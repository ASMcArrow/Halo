#include "HaloRun.hh"
#include "G4SDManager.hh"

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
        Cells[i] = new G4double[70];
        for (int j = 0; j < 70; j++)
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
        HaloDetectorHitsCollection* HC = (HaloDetectorHitsCollection*)(HCE -> GetHC(CollectionID));
        if(HC!=NULL)
        {
            //HaloDetectorHit *hit = 0;
            for (G4int k = 0; k < HC->entries(); k++)
            {
                HaloDetectorHit *hit = (HaloDetectorHit*)(HC->GetHit(k));
                if (Verbose)
                {
                    G4cout << "HitsVector Initial: " << "k = "<< k << " Energy deposition is " << hit->GetEdep()
                           << " Position is" << hit->GetPos()[0] << G4endl;
                }

                G4int i = hit->GetPos()[0];
                G4int j = hit->GetPos()[1];
                Cells[i][j] += hit->GetEdep();
            }
        }
    }
}

void HaloRun::Merge(const G4Run * aRun)
{
    const HaloRun *localRun = static_cast<const HaloRun*>(aRun);

    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 70; j++)
            Cells[i][j] += localRun->Cells[i][j];
    }

    G4Run::Merge(aRun);
}


