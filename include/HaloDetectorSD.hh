#ifndef HaloDETECTORSD_H
#define HaloDETECTORSD_H

#include "G4VSensitiveDetector.hh"
#include "HaloDetectorHit.hh"
#include "globals.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class HaloDetectorSD : public G4VSensitiveDetector
{

public:
  HaloDetectorSD(G4String name);
  ~HaloDetectorSD();

  void Initialize(G4HCofThisEvent* ); 
  G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* obsolete);
  void EndOfEvent(G4HCofThisEvent* HCE);
 
private:
  HaloDetectorHitsCollection* HitsCollection;
  G4String SensitiveDetectorName;
};
#endif


