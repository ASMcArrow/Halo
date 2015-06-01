#ifndef HaloDETECTORHIT_H
#define HaloDETECTORHIT_H

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class HaloDetectorHit : public G4VHit
{

public:
    HaloDetectorHit();
    ~HaloDetectorHit();
 
    HaloDetectorHit(const HaloDetectorHit &right);
    const HaloDetectorHit& operator = (const HaloDetectorHit &right);
    int operator == (const HaloDetectorHit &right) const;

    inline void *operator new(size_t);
    inline void operator delete(void *aHit);

    void Draw();
 // void Print() {} const;

    void SetEdep(G4double de)
    { EnergyDeposit = de; }

    G4double GetEdep() const
    { return EnergyDeposit; }

    void SetPos(G4ThreeVector xyz)
    { Position = xyz; }

    G4ThreeVector GetPos() const
    { return Position; }

    void SetArea(G4double area)
    { Area = area; }

    G4double GetArea() const
    { return Area; }

private:
    G4ThreeVector Position; // Position
    G4double EnergyDeposit; // Energy deposit associated with the hit
    G4double Area; // Area of the cell where this energy deposition occured
};

typedef G4THitsCollection<HaloDetectorHit> HaloDetectorHitsCollection;
extern G4ThreadLocal G4Allocator<HaloDetectorHit>* HaloDetectorHitAllocator;

inline void* HaloDetectorHit::operator new(size_t)
{
    if(!HaloDetectorHitAllocator)
        HaloDetectorHitAllocator = new G4Allocator<HaloDetectorHit>;

    return (void *)HaloDetectorHitAllocator->MallocSingle();
}

inline void HaloDetectorHit::operator delete(void *aHit)
{
    HaloDetectorHitAllocator->FreeSingle((HaloDetectorHit*) aHit);
}

#endif


