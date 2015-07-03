#include "HaloParallelWorld.hh"
#include "HaloCylinderParameterisation.hh"

#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"
#include "G4PVReplica.hh"
#include "G4VisAttributes.hh"
#include "G4SDManager.hh"
#include "G4PVDivision.hh"
#include "G4PVParameterised.hh"
#include "G4PSDoseDeposit3D.hh"

HaloParallelWorld::HaloParallelWorld(G4String worldName)
    :G4VUserParallelWorld(worldName)
{}

HaloParallelWorld::~HaloParallelWorld()
{}

void HaloParallelWorld::Construct()
{
    G4VPhysicalVolume *ghostWorld = GetWorld();
    G4LogicalVolume *worldLog = ghostWorld->GetLogicalVolume();

    // Place volumes in the parallel world here
    //  detHalfDimension = (0.375628575/2.0)*cm;
    // sG4double nDivisions = 250.0;

    G4Tubs *ghostTubsDetector = new G4Tubs("GhostTubsDetector", 0*cm, 10*cm+0.5*mm, 12.5*cm, 0.*M_PI*rad, 2.*M_PI*rad);
    G4LogicalVolume *ghostTubsDetectorLog = new G4LogicalVolume(ghostTubsDetector, 0, "GhostTubsDetectorLog");
    new G4PVPlacement(0, G4ThreeVector(0, 0, 12.5*cm), ghostTubsDetectorLog, "GhostTubsDetectorPhys", worldLog, 0, 0);

    G4VSolid* ghostRhoTubsDetector = new G4Tubs("GhostRhoTubsDetector", 0*cm, 10*cm+0.5*mm, 0.5*mm, 0.*M_PI*rad, 2.*M_PI*rad);
    LogicGhostRhoTubsDetector = new G4LogicalVolume(ghostRhoTubsDetector, 0, "LogicGhostRhoTubsDetector");
    G4VPVParameterisation* cylinderParam = new HaloCylinderParameterisation;
    new G4PVParameterised("Cylinders", LogicGhostRhoTubsDetector, ghostTubsDetectorLog, kZAxis, 303, cylinderParam);

    G4VisAttributes* visAttributes = new G4VisAttributes;
    visAttributes->SetColor(0,1,1);
    LogicGhostRhoTubsDetector->SetVisAttributes(visAttributes);
}

void HaloParallelWorld::ConstructSD()
{
    G4SDManager::GetSDMpointer()->SetVerboseLevel(1);
    G4MultiFunctionalDetector* detector = new G4MultiFunctionalDetector("Detector");
    G4VPrimitiveScorer* doseSD = new G4PSDoseDeposit("Dose");
   // doseSD->SetUnit("MeV/g");
    detector->RegisterPrimitive(doseSD);
    G4cout << "DOSE SCORER " << doseSD->GetUnit() << G4endl;
    SetSensitiveDetector(LogicGhostRhoTubsDetector, detector);
}







// Division along X axis: the detector is divided in slices along the X axis

/*G4double halfXVoxelSizeX = halfDetectorSizeX/m_NumberOfVoxelsAlongX;
G4double halfXVoxelSizeY = halfDetectorSizeY;
G4double halfXVoxelSizeZ = halfDetectorSizeZ;
G4double voxelXThickness = 2*halfXVoxelSizeX;

G4Box *ghostXDivision = new G4Box("ghostXDivision",
                 halfXVoxelSizeX,
                 halfXVoxelSizeY,
                 halfXVoxelSizeZ);

G4LogicalVolume *ghostXDivisionLog = new G4LogicalVolume(ghostXDivision,
                               dummyMat,
                               "ghostXDivisionLog",
                               0,0,0);

G4VPhysicalVolume *ghostXDivisionPhys = new G4PVReplica("ghostXDivisionPhys",
                                                          ghostXDivisionLog,
                                                          ghostPhys,
                                                          kXAxis,
                                                          numberOfVoxelsAlongX,
                                                          voxelXThickness);*/

// Division along Y axis: the slices along the X axis are divided along the Y axis

/* G4double halfYVoxelSizeX = halfXVoxelSizeX;
G4double halfYVoxelSizeY = halfDetectorSizeY/numberOfVoxelsAlongY;
G4double halfYVoxelSizeZ = halfDetectorSizeZ;
G4double voxelYThickness = 2*halfYVoxelSizeY;

G4Box *ghostSector = new G4Box("ghostSector",
                halfYVoxelSizeX,
                halfYVoxelSizeY,
                halfYVoxelSizeZ);

G4LogicalVolume *ghostSectorLog = new G4LogicalVolume(ghostSector,
                               dummyMat,
                               "ghostSectorLog",
                               0,0,0);

G4VPhysicalVolume *ghostSectorPhys = new G4PVReplica("ghostSectorPhys",
                              ghostSectorLog,
                              ghostXDivisionPhys,
                              kYAxis,
                              numberOfVoxelsAlongY,
                              voxelYThickness);*/

// Division along Z axis: the slices along the Y axis are divided along the Z axis

/*  G4double halfZVoxelSizeX = m_DetectorSizeX;
G4double halfZVoxelSizeY = m_DetectorSizeY;
G4double halfZVoxelSizeZ = m_DetectorSizeZ/m_NumberOfVoxelsAlongZ;
G4double voxelZThickness = 2*halfZVoxelSizeZ;

G4Box *ghostZDivision = new G4Box("ghostZDivision",
                halfZVoxelSizeX,
                halfZVoxelSizeY,
                halfZVoxelSizeZ);

G4LogicalVolume *ghostZDivisionLog = new G4LogicalVolume(ghostZDivision,
                               dummyMat,
                               "ghostZDivisionLog",
                               0,0,0);
ghostZDivisionLog->SetSensitiveDetector(detector);

ghostZDivisionPhys = new G4PVReplica("ghostZDivisionPhys",
                                        ghostZDivisionLog,
                                        ghostPhys,
                                        kZAxis,
                                        m_NumberOfVoxelsAlongZ,
                                        voxelZThickness);*/
