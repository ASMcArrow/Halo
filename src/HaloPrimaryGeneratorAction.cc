#include "HaloPrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SingleParticleSource.hh"
#include "G4SPSAngDistribution.hh"
#include "G4SPSPosDistribution.hh"
#include "CLHEP/Units/SystemOfUnits.h"
#include "G4Proton.hh"
#include "globals.hh"
#include "Randomize.hh"
#include "G4GeneralParticleSource.hh"

using namespace CLHEP;

HaloPrimaryGeneratorAction::HaloPrimaryGeneratorAction()
{
    CircleSource = new G4SingleParticleSource;
    CircleSource->SetParticleDefinition(G4Proton::Definition());

    G4SPSEneDistribution* energy = CircleSource->GetEneDist();
    energy->SetEnergyDisType("Gauss");
    energy->SetBeamSigmaInE(1.1557 *MeV);
    energy->SetMonoEnergy(177.9 *MeV);

    G4SPSPosDistribution* position = CircleSource->GetPosDist();
    position->SetPosDisType("Beam");
    position->SetBeamSigmaInR(0.54*cm);
    position->SetCentreCoords(G4ThreeVector(0*m, 0*m, - 1*mm));

    G4SPSAngDistribution* angular = CircleSource->GetAngDist();
    angular->SetAngDistType("beam2d");
    angular->SetParticleMomentumDirection(G4ThreeVector(0.0,0.0,1.0));
    angular->DefineAngRefAxes("angref1", G4ThreeVector(-1.0,0.0,0.0));
    angular->SetBeamSigmaInAngY(13*mrad);
    angular->SetBeamSigmaInAngX(13*mrad);
    CircleSource->SetNumberOfParticles(1);
}

HaloPrimaryGeneratorAction::~HaloPrimaryGeneratorAction()
{
    delete CircleSource;
}

void HaloPrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
    CircleSource->GeneratePrimaryVertex(event);
}
