#ifndef HaloPRIMARYGENERATORACTION_H
#define HaloPRIMARYGENERATORACTION_H

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4SPSPosDistribution.hh"
#include "G4Types.hh"
#include "G4SingleParticleSource.hh"

class G4Event;

class HaloPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{

public:
    HaloPrimaryGeneratorAction();
    ~HaloPrimaryGeneratorAction();

    void GeneratePrimaries(G4Event* event);

private:
    G4SingleParticleSource* CircleSource;
};

#endif


