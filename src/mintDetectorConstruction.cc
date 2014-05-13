#include "mintDetectorConstruction.hh"

#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4Box.hh"
#include "G4Trd.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4SDManager.hh"
#include "G4FieldManager.hh"

#include "DetSD.hh"

mintDetectorConstruction::mintDetectorConstruction()
:block_PVName("BlockPV")
{
  ConstructMaterials();
  DefineDimensions();
}

mintDetectorConstruction::~mintDetectorConstruction()
{
  DestructMaterials();
}

void mintDetectorConstruction::DefineDimensions()
{
  //Lab
  labX = 1000*mm;
  labY = 1000*mm;
  labZ = 1000*mm;

  //Neutron Detector
  //block_dxy = 100*mm;
  //block_dz  = 200*mm;
  block_dxy = 10*mm;
  block_dz  = 100*mm;
  block_z   = 200*mm;
}

G4VPhysicalVolume* mintDetectorConstruction::Construct()
{
  G4VSolid* labSolid = new G4Box("labSolid", labX/2, labY/2, labZ/2);
  G4LogicalVolume* labLV = new G4LogicalVolume(labSolid, Air, "labLV");
  G4VPhysicalVolume* labPV = new G4PVPlacement(0, G4ThreeVector(), "labPV", labLV, 0, false, 0);

  G4SDManager* sdManager = G4SDManager::GetSDMpointer();

  ConstructBlock(labPV, sdManager);

  return labPV;
}


//Block Detector (for neutron)
void mintDetectorConstruction::ConstructBlock(G4VPhysicalVolume* labPV, G4SDManager* sdManager)
{
  G4VSolid* BlockSolid = new G4Box("Block", block_dxy/2, block_dxy/2, block_dz/2);
  G4LogicalVolume* BlockLV = new G4LogicalVolume(BlockSolid, Scint, "BlockLV");
  new G4PVPlacement(0, G4ThreeVector(0,0,block_z+block_dz/2), block_PVName, BlockLV, labPV, false, 0);

  DetSD* blockSD = new DetSD("/block", block_PVName);
  sdManager -> AddNewDetector(blockSD);
  BlockLV -> SetSensitiveDetector(blockSD);
}


void mintDetectorConstruction::ConstructMaterials()
{
  const G4double labTemp = STP_Temperature + 20.*kelvin;

  G4double density_PET = 1.4*g/cm3;
  G4double density_Ar  = 1.782e-3*g/cm3; //gas
  G4double density_CO2 = 1.839e-3*g/cm3; //gas
  G4double density_C10 = 0.9*density_Ar + 0.1*density_CO2; //gas

  elN  = new G4Element("Nitrogen", "N",  7,  14.000674*g/mole);
  elO  = new G4Element("Oxygen",   "O",  8,  15.9994*g/mole);
  elAr = new G4Element("Argon",    "Ar", 18, 39.938*g/mole);
  elC  = new G4Element("Carbon",   "C",  6,  12.011*g/mole);
  elH  = new G4Element("Hydrogen", "H",  1,  1.00794*g/mole);

  Air = new G4Material("Air", 1.2929e-03*g/cm3, 3, kStateGas, labTemp);
    Air -> AddElement(elN, 75.47/99.95);
    Air -> AddElement(elO, 23.20/99.95);
    Air -> AddElement(elAr, 1.28/99.95);

  Ar = new G4Material("Ar", density_Ar, 1, kStateGas, labTemp);
    Ar -> AddElement(elAr,1);

  CO2 = new G4Material("CO2", density_CO2, 2, kStateGas, labTemp);
    CO2 -> AddElement(elC,1);
    CO2 -> AddElement(elO,2);

  C10 = new G4Material("C10", density_C10, 2, kStateGas, labTemp);
    C10 -> AddMaterial(CO2, 0.1*density_CO2/density_C10);
    C10 -> AddMaterial(Ar, 0.9*density_Ar/density_C10);

  PET = new G4Material("PET", density_PET, 3, kStateSolid);
    PET -> AddElement(elC,10);
    PET -> AddElement(elH,8);
    PET -> AddElement(elO,4);

  Scint = new G4Material("Scintillator", 1.05*g/cm3, 2, kStateSolid, labTemp);
    Scint -> AddElement(elC, 10);
    Scint -> AddElement(elH, 11);
}

void mintDetectorConstruction::DestructMaterials()
{
  delete Air;
  delete Ar;
  delete CO2;
  delete C10;

  delete elH;
  delete elC;
  delete elAr;
  delete elO;
  delete elN;
}
