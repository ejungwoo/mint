#ifndef mintField_hh
#define mintField_hh 1

#include "mintDetectorConstruction.hh"
#include "G4FieldManager.hh"

class mintDetectorConstruction;

class mintField
{
  public:
    mintField(G4FieldManager*, mintDetectorConstruction*);
    //mintField();
    ~mintField();

    void SetLocalField();
    void SetGlobalField();

  private:
    G4FieldManager* fieldManager;
    mintDetectorConstruction* mintDC;
    G4MagneticField* solenoidField;
};

#endif
