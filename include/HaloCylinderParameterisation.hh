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
        G4int row = copyNo/3;
        // G4double detHalfDimension = (0.375628575/2.0);

        G4double innerRadius =  ((G4double)row)*mm-0.5*mm;
        G4double outerRadius = ((G4double)row)*mm+0.5*mm;

        if (innerRadius < 0)
        {
            innerRadius = 0;
        }

        //        if (row == 3)
        //        {
        //           innerRadius =  ((G4double)row)*cm-detHalfDimension*cm-0.2*cm;
        //           outerRadius = ((G4double)row)*cm+detHalfDimension*cm-0.2*cm;
        //        }

        cylinder.SetInnerRadius(innerRadius);
        cylinder.SetOuterRadius(outerRadius);
    }

    virtual void ComputeTransformation(const G4int copyNo, G4VPhysicalVolume *physVol ) const
    {
        G4int column = copyNo%3;
        // G4double detHalfDimension = (0.375628575/2.0)*cm;
        G4double z[] = {20, 120, 210};
        physVol->SetTranslation(G4ThreeVector(0, 0, (-12.5*cm + z[column]*mm)));
        physVol->SetRotation(0);
    }
};

#endif // HALOCYLINDERPARAMERETIZATION_HH

