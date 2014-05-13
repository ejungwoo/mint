#ifndef SolenoidField_hh
#define SolenoidField_hh 1

#include "G4MagneticField.hh"
#include "G4ThreeVector.hh"

#include "TFile.h"
#include "TTree.h"
#include "TH2D.h"

class TFile;
class TTree;
class TH2D;

class SolenoidField : public G4MagneticField
{
  public:
    SolenoidField();
    ~SolenoidField();
    void SetFieldValue();

    void GetFieldValue(const G4double Point[3], G4double* Bfield) const;

  private:
    TFile *fieldData;
    TTree *fieldTree;

    TH2D *histBR;
    TH2D *histBZ;
};
#endif
