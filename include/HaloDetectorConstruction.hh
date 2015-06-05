#ifndef HALODETECTORCONSTRUCTION_H
#define HALODETECTORCONSTRUCTION_H

#include "G4VUserDetectorConstruction.hh"
#include "G4Material.hh"

class G4LogicalVolume;
class G4VPhysicalVolume;

using namespace CLHEP;

class HaloDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    HaloDetectorConstruction() {}
    ~HaloDetectorConstruction() {}

    G4VPhysicalVolume* Construct();

 // void ConstructSDandField();
 // This method is used in multi-threaded applications to build
 // per-worker non-shared objects: SensitiveDetectors and Field managers

private:
    void InitializeMaterials();
    std::map <std::string, G4Material*> MaterialMap;};

#endif

