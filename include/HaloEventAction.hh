#ifndef HALOEVENTACTION_H
#define HALOEVENTACTION_H

#include "G4UserEventAction.hh"
#include "G4LogicalVolume.hh"
#include "globals.hh"

class HaloEventAction : public G4UserEventAction
{

public:
    HaloEventAction();
    ~HaloEventAction();

    void BeginOfEventAction(const G4Event* event);
    void EndOfEventAction(const G4Event* event);
};

#endif

    
