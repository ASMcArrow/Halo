#ifndef HaloPARALLELWORLD_H
#define HaloPARALLELWORLD_H

#include "globals.hh"
#include "G4VUserParallelWorld.hh"
#include "CLHEP/Units/SystemOfUnits.h"

using namespace CLHEP;

class HaloParallelWorld : public G4VUserParallelWorld
{
public:
    HaloParallelWorld(G4String worldName);
    ~HaloParallelWorld();

    void Construct();
    void ConstructSD();

private:
    G4LogicalVolume *GhostDetectorLog;
    G4LogicalVolume *GhostXBoxLog;
    G4LogicalVolume *GhostYBoxLog;
};
#endif

