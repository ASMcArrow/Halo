#ifndef HALOCYLINDERPARAMERETIZATION_HH
#define HALOCYLINDERPARAMERETIZATION_HH

#include "G4VPVParameterisation.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Tubs.hh"

class HaloCylinderParameterisation : public G4VPVParameterisation
{
public:
    HaloCylinderParameterisation() {}
    virtual ~HaloCylinderParameterisation(){}

    void ComputeDimensions (G4Tubs& cylinder, const G4int copyNo, const G4VPhysicalVolume* physVol) const
    {
        G4int row = copyNo/70;
        G4double detHalfDimension = (0.375628575/2.0);
        G4double innerRadius =  ((G4double)row)*cm-detHalfDimension*cm;

        if (innerRadius < 0)
            innerRadius = 0;

        G4double outerRadius = ((G4double)row)*cm+detHalfDimension*cm;

        cylinder.SetInnerRadius(innerRadius);
        cylinder.SetOuterRadius(outerRadius);
    }

    virtual void ComputeTransformation(const G4int copyNo, G4VPhysicalVolume *physVol ) const
    {
        G4int column = copyNo%70;
        G4double detHalfDimension = (0.375628575/2.0)*cm;
        physVol->SetTranslation(G4ThreeVector(0, 0, -detHalfDimension*70.0+detHalfDimension+2.0*column*detHalfDimension));
        physVol->SetRotation(0);
    }
};

#endif // HALOCYLINDERPARAMERETIZATION_HH

