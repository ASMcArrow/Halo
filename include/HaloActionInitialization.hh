#ifndef HALOACTIONINITIASLIZATION_HH
#define HALOACTIONINITIASLIZATION_HH

#include "G4VUserActionInitialization.hh"

class HaloActionInitialization : public G4VUserActionInitialization
{
  public:

    HaloActionInitialization();
    virtual ~HaloActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

#endif // HALOACTIONINITIASLIZATION_HH
