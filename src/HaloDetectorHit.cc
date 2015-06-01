#include "HaloDetectorHit.hh"

#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

G4ThreadLocal G4Allocator<HaloDetectorHit>* HaloDetectorHitAllocator = 0;

HaloDetectorHit::HaloDetectorHit()
{
    EnergyDeposit = 0;
    Position.set(0,0,0);
    Area = 0;
}

HaloDetectorHit::~HaloDetectorHit()
{}

HaloDetectorHit::HaloDetectorHit(const HaloDetectorHit &right)
    :G4VHit()
{
   Position = right.Position;
   EnergyDeposit = right.EnergyDeposit;
   Area = right.Area;
}

const HaloDetectorHit&
HaloDetectorHit::operator=(const HaloDetectorHit &right)
{
    Position = right.Position;
    EnergyDeposit = right.EnergyDeposit;
    Area = right.Area;

    return *this;
}

void HaloDetectorHit::Draw()
{
    G4Circle circle(Position);
    circle.SetScreenDiameter(10.0);
    circle.SetFillStyle (G4Circle::filled);
    G4Colour colour(1.,0.,0.);
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);
}

int HaloDetectorHit::operator==(const HaloDetectorHit &right) const
{
    return((Position==right.Position)&&(EnergyDeposit==right.EnergyDeposit))&&(Area==right.Area);
}


