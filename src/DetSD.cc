#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"
#include "DetSD.hh"
#include "DetHit.hh"
#include <iostream>

DetSD::DetSD(const G4String &name, const G4String pv_name)
:G4VSensitiveDetector(name), PVName(pv_name)
{
  collectionName.insert("DetHitsCollection");
}

DetSD::~DetSD()
{
}

void DetSD::Initialize(G4HCofThisEvent *HCTE)
{
  hitsCollection = new G4THitsCollection<DetHit>(SensitiveDetectorName, collectionName[0]);

  G4int hcid = G4SDManager::GetSDMpointer() -> GetCollectionID(collectionName[0]);
  HCTE -> AddHitsCollection(hcid, hitsCollection);
}
  
G4bool DetSD::ProcessHits(G4Step *aStep, G4TouchableHistory *ROHistory)
{
  energyDeposit = aStep -> GetTotalEnergyDeposit();

  if(energyDeposit == 0.) return false;

  if((aStep -> GetPreStepPoint() -> GetPhysicalVolume() -> GetName() == PVName))
  {
    parentID    = aStep -> GetTrack() -> GetParentID();
    pID         = aStep -> GetTrack() -> GetDefinition() -> GetPDGEncoding();
    direction   = aStep -> GetTrack() -> GetMomentumDirection();
    prePosition = aStep -> GetPreStepPoint() -> GetPosition();
    time        = aStep -> GetPreStepPoint() -> GetGlobalTime();

    DetHit *aHit = new DetHit(parentID, pID, direction, prePosition, time, energyDeposit);
    hitsCollection -> insert(aHit);
  }

  return true;
}

void DetSD::EndOfEvent(G4HCofThisEvent *HCTE)
{
}
