#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"

#include "mintPrimaryGeneratorAction.hh"
#include "mintEventAction.hh"
#include "mintDataFile.hh"
#include "DetHit.hh"

#include <fstream>
#include <iomanip>

#include <TFile.h>
#include <TTree.h>

mintEventAction::mintEventAction(mintDataFile* mintDF, mintPrimaryGeneratorAction *mintPGAPointer)
: dataFile(mintDF), mintPGA(mintPGAPointer)
{
}

mintEventAction::~mintEventAction()
{
}

void mintEventAction::BeginOfEventAction(const G4Event* anEvent)
{
}

void mintEventAction::EndOfEventAction(const G4Event* anEvent)
{
  G4SDManager* sdManager = G4SDManager::GetSDMpointer();

  G4HCofThisEvent* HCTE = anEvent -> GetHCofThisEvent();
  if (!HCTE) return;

  G4THitsCollection<DetHit>* HC_Det = NULL;

  hitsCollectionID = sdManager -> GetCollectionID("DetHitsCollection");
  HC_Det = (G4THitsCollection<DetHit> *)(HCTE -> GetHC(hitsCollectionID));
  
  if(HC_Det)
  {
    G4int numHits = HC_Det -> entries();

    for(G4int i=0; i!=numHits; i++)
    {
      G4ThreeVector prePosition  = (*HC_Det)[i] -> GetPrePosition();
      G4ThreeVector direction  = (*HC_Det)[i] -> GetDirection();
      G4int pID  = (*HC_Det)[i] -> GetParentID();
      G4int parentID  = (*HC_Det)[i] -> GetPID();
      G4double time= (*HC_Det)[i] -> GetTime();
      G4double energyDeposit= (*HC_Det)[i] -> GetEdep();
      
      G4double track_theta = direction.theta();

      dataFile -> Fill(prePosition.x(),
                       prePosition.y(),
                       prePosition.z(),
                       track_theta,
                       pID,
                       parentID,
                       time,
                       energyDeposit);
    }
  }
  mintPGA -> EndOfTrack();
}
