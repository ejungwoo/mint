#include "SolenoidField.hh"

#include "globals.hh"
#include "G4ThreeVector.hh"

#include "TFile.h"
#include "TTree.h"
#include "TMath.h"

SolenoidField::SolenoidField()
{
  SetFieldValue();
}

SolenoidField::~SolenoidField()
{
  delete fieldData;
  delete histBR;
  delete histBZ;
}

void SolenoidField::SetFieldValue()
{
  int radius, zPosition;
  double BfieldR, BfieldZ;

  fieldData = new TFile("data/solenoid.root");
  fieldTree = (TTree*) fieldData -> Get("field");
  fieldTree -> SetBranchAddress("r",&radius);
  fieldTree -> SetBranchAddress("z",&zPosition);
  fieldTree -> SetBranchAddress("br",&BfieldR);
  fieldTree -> SetBranchAddress("bz",&BfieldZ);

  histBR = new TH2D("histBR","",100,0,1000,200,-700,1300);
  histBZ = new TH2D("histBZ","",100,0,1000,200,-700,1300);
  
  int entries = fieldTree -> GetEntries();
  for(int i=0; i<entries; i++)
  {
    fieldTree -> GetEntry(i);
    histBR -> Fill(radius,zPosition,BfieldR);
    histBZ -> Fill(radius,zPosition,BfieldZ);
  }
}

void SolenoidField::GetFieldValue(const G4double Point[3], G4double* Bfield) const
{
  double rIn  = 1.0*m;
  double zMin = -1.0*m;
  double zMax = 1.0*m;

  double zOffset = 0.3*m;

  double phi = (double)TMath::ATan2(Point[1],Point[0]);
  double radius = (double)sqrt(Point[0]*Point[0]+Point[1]*Point[1]);
  double zPosition = (double)Point[2];

  double BfieldR;

  if(zPosition<zMax && zPosition>zMin && radius<rIn)
  {
    zPosition += zOffset;
    Bfield[2] = (histBZ -> Interpolate(radius,zPosition))*tesla;
    BfieldR = histBR -> Interpolate(radius,zPosition);
    Bfield[0] = BfieldR*TMath::Cos(phi)*tesla;
    Bfield[1] = BfieldR*TMath::Sin(phi)*tesla;
  }
  else
  {
  Bfield[0] = 0.;
  Bfield[1] = 0.;
  Bfield[2] = 0.;
  }
}
