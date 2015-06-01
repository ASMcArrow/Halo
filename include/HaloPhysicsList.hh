#ifndef HaloPHYSICSLIST_H
#define HaloPHYSICSLIST_H

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

class HaloPhysicsList: public G4VModularPhysicsList
{
public:

  HaloPhysicsList();
  virtual ~HaloPhysicsList();

  void SetCuts();
  void AddParallelScoring();
  void ConstructProcess();

private:
  G4double cutForGamma;
  G4double cutForElectron;
  G4double cutForPositron;
};

#endif
