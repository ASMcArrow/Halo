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
        G4double detHalfDimension = (0.4/2.0)*cm;
        G4double innerRadius =  0;
        G4double outerRadius = 0;

       // if (row <= 4)
     //   {

            innerRadius =  ((G4double)row)*detHalfDimension*2-detHalfDimension;
            outerRadius = ((G4double)row)*detHalfDimension*2+detHalfDimension;

            if (innerRadius < 0)
            {
                innerRadius = 0;
            }

            //        if (row == 3)
            //        {
            //            innerRadius =  ((G4double)row)*cm-0.5*cm*cm-0.2*cm;
            //            outerRadius = ((G4double)row)*cm+0.5*cm-0.2*cm;
            //        }
//        }
//        else
//        {
//            innerRadius =  ((G4double)row)*cm-0.5*cm;
//            outerRadius = ((G4double)row)*cm+0.5*cm;
//        }

        cylinder.SetInnerRadius(innerRadius);
        cylinder.SetOuterRadius(outerRadius);
    }

    virtual void ComputeTransformation(const G4int copyNo, G4VPhysicalVolume *physVol ) const
    {
        G4int column = copyNo%3;
        G4double detHalfDimension = (0.4/2.0)*cm;
        G4double z[] = {20, 120, 210};
        physVol->SetTranslation(G4ThreeVector(0, 0, (-0.5*mm*250+0.5*mm+z[column]*mm)));
        physVol->SetRotation(0);
    }
};

#endif // HALOCYLINDERPARAMERETIZATION_HH

