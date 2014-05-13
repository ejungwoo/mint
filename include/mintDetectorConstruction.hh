#ifndef mintDetectorConstrution_h
#define mintDetectorConstrution_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"

#include "G4Element.hh"
#include "G4Material.hh"
#include "G4SDManager.hh"
#include "G4FieldManager.hh"

class G4VPhysicalVolume;

class mintDetectorConstruction: public G4VUserDetectorConstruction
{
  public:
    mintDetectorConstruction();
    virtual ~mintDetectorConstruction();
    virtual G4VPhysicalVolume* Construct();

    void SetFieldToTPC(G4FieldManager* fieldManager);

  private:
    void ConstructBlock(G4VPhysicalVolume* labPV, G4SDManager* sdManager);
    
    void DefineDimensions();
    void ConstructMaterials();
    void DestructMaterials();

    G4FieldManager*  fieldManager;

    G4Element* elN;
    G4Element* elO;
    G4Element* elAr;
    G4Element* elC;
    G4Element* elH;

    G4Material* Air;
    G4Material* Ar;
    G4Material* CO2;
    G4Material* C10;
    G4Material* PET;
    G4Material* Scint;

    //lab
    G4double labX, labY, labZ;

    //block neutron detecotr
    const G4String block_PVName;
    G4double block_dxy, block_dz, block_z;
};
#endif
