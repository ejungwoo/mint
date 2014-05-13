#ifndef DETSD_h
#define DETSD_h 1

#include "G4VSensitiveDetector.hh"
#include "G4ThreeVector.hh"
#include "DetHit.hh"

class G4HCofThisEvent;
class G4Step;
class G4TouchableHistory;

class DetSD: public G4VSensitiveDetector
{
  public: 
    DetSD(const G4String& name, const G4String pv_name);
    virtual ~DetSD();

    const G4String PVName;

    virtual G4bool ProcessHits(G4Step *aStep, G4TouchableHistory *ROHist);
    virtual void Initialize(G4HCofThisEvent *HCTE);
    virtual void EndOfEvent(G4HCofThisEvent *HCTE);

    G4double      time, parentID, pID, energyDeposit;
    G4ThreeVector direction, prePosition;

  private:
    G4THitsCollection<DetHit> *hitsCollection;
};
#endif
