#include "mintField.hh"
#include "mintDetectorConstruction.hh"
#include "G4FieldManager.hh"
#include "G4UniformMagField.hh"
#include "G4TransportationManager.hh"

#include "SolenoidField.hh"

mintField::mintField(G4FieldManager* fieldManagerPointer, mintDetectorConstruction* mintDCPointer)
:fieldManager(fieldManagerPointer), mintDC(mintDCPointer)
{
  //solenoidField = new G4UniformMagField(G4ThreeVector(0.,0.,3*tesla));
  solenoidField = new SolenoidField();
}

mintField::~mintField()
{
  delete solenoidField;
}

void mintField::SetGlobalField()
{
  //fieldManager = G4TransportationManager::GetTransportationManager() -> GetFieldManager();
  fieldManager -> SetDetectorField(solenoidField);
  fieldManager -> CreateChordFinder(solenoidField);
}
