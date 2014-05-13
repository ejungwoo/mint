#ifndef DetHit_h
#define DetHit_h 1

#include "G4ThreeVector.hh"
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"

class DetHit: public G4VHit
{
  private:
    G4int parentID;
    G4int pID;
    G4ThreeVector direction;
    G4ThreeVector prePos;
    G4double time;
    G4double energyDeposit;

  public:
    DetHit();
    DetHit(G4int, G4int, G4ThreeVector, G4ThreeVector, G4double, G4double);
    virtual ~DetHit();

    DetHit(const DetHit &right);
    const DetHit &operator=(const DetHit &right);

    void *operator new(size_t);
    void operator delete(void *aHit);

    G4ThreeVector GetPrePosition() const { return prePos; };
    G4ThreeVector GetDirection() const { return direction; };
    G4int GetParentID() const { return parentID; };
    G4int GetPID() const { return pID; };
    G4double GetEdep() const { return energyDeposit; };
    G4double GetTime() const { return time; };
};

inline DetHit::DetHit(const DetHit &right)
:G4VHit()
{
  prePos = right.prePos;
  direction = right.direction;
  parentID = right.parentID;
  pID = right.pID;
  energyDeposit = right.energyDeposit;
  time = right.time;
}

inline const DetHit &DetHit::operator=(const DetHit &right)
{
  prePos = right.prePos;
  direction = right.direction;
  parentID = right.parentID;
  pID = right.pID;
  energyDeposit = right.energyDeposit;
  time = right.time;

  return *this;
}

extern G4Allocator<DetHit> DetHitAllocator;

inline void *DetHit::operator new(size_t)
{
  void *aHit = (void *)DetHitAllocator.MallocSingle();
  return aHit;
}

inline void DetHit::operator delete(void *aHit)
{
  DetHitAllocator.FreeSingle((DetHit *) aHit);
}

#endif
