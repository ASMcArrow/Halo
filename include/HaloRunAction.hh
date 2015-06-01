#ifndef HaloRUNACTION_H
#define HaloRUNACTION_H

#include "G4UserRunAction.hh"
#include "globals.hh"
#include <vector>

class HaloRunAction : public G4UserRunAction
{
public:

    HaloRunAction(const G4String detectorName);
    virtual ~HaloRunAction();

    virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);

private:
    G4String DetectorName;
    G4double Cells[200][200];
};

#endif




