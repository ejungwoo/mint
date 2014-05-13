#include "DetHit.hh"

G4Allocator<DetHit> DetHitAllocator;

// allocator
DetHit::DetHit()
:prePos(G4ThreeVector(0,0,0)), energyDeposit(0)
{
}

DetHit::DetHit(G4int parentID_p, G4int pID_p, G4ThreeVector direction_p, G4ThreeVector prePos_p, G4double time_p, G4double edep)
:parentID(parentID_p), pID(pID_p), direction(direction_p), prePos(prePos_p), time(time_p), energyDeposit(edep)
{
}

DetHit::~DetHit()
{
}
