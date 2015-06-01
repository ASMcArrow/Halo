#include "HaloActionInitialization.hh"
#include "HaloPrimaryGeneratorAction.hh"
#include "HaloRunAction.hh"

HaloActionInitialization::HaloActionInitialization()
    : G4VUserActionInitialization()
{}

HaloActionInitialization::~HaloActionInitialization()
{}

void HaloActionInitialization::BuildForMaster() const
{
    SetUserAction(new HaloRunAction("FilmDetector"));
}

void HaloActionInitialization::Build() const
{
    SetUserAction(new HaloPrimaryGeneratorAction);
    SetUserAction(new HaloRunAction("FilmDetector"));
}
