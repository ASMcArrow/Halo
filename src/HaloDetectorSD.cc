#include "HaloDetectorSD.hh"
#include "HaloDetectorHit.hh"

#include "G4Step.hh"
#include "G4VTouchable.hh"
#include "G4VProcess.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"

#include <cstdio>

HaloDetectorSD::HaloDetectorSD(G4String name):
    G4VSensitiveDetector(name)
{ 
    G4String HCname;
    collectionName.insert(HCname="HaloDetectorHitsCollection");
    HitsCollection = NULL;
    SensitiveDetectorName = name;
}

HaloDetectorSD::~HaloDetectorSD()
{}

void
HaloDetectorSD::Initialize(G4HCofThisEvent*)
{
    HitsCollection = new HaloDetectorHitsCollection(SensitiveDetectorName,
                                                           collectionName[0]);
}

G4bool
HaloDetectorSD::ProcessHits(G4Step* aStep, G4TouchableHistory* obsolete)
{
    G4StepPoint* preStep = aStep->GetPreStepPoint();
    G4TouchableHistory* touchable = (G4TouchableHistory*)(preStep->GetTouchable());

    G4int i = touchable->GetReplicaNumber(0);
    G4int j = touchable->GetReplicaNumber(1);
    G4double energyDeposit = aStep->GetTotalEnergyDeposit();

    if((energyDeposit != 0)&&(i >= 0 /*In case of blocked volume*/))
	{
        HaloDetectorHit* detectorHit = new HaloDetectorHit();
        detectorHit->SetEdep(energyDeposit);
        detectorHit->SetPos(G4ThreeVector(i, j, 0));
        HitsCollection->insert(detectorHit);

        return true;
    }

    return false;
}

void
HaloDetectorSD::EndOfEvent(G4HCofThisEvent* HCE)
{
    int HCID = GetCollectionID(0);
    HCE->AddHitsCollection(HCID, HitsCollection);
}

