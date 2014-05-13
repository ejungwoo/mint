#ifndef EXMAPLEEVENTACTION_H
#define EXMAPLEEVENTACTION_H 1

#include "G4UserEventAction.hh"
#include "mintPrimaryGeneratorAction.hh"
#include "mintDataFile.hh"

class G4Event;

class mintEventAction: public G4UserEventAction
{
  public:
    mintEventAction(mintDataFile *mintDF, mintPrimaryGeneratorAction* mintPGAPointer);
    virtual ~mintEventAction();

    virtual void BeginOfEventAction(const G4Event* anEvent);
    virtual void EndOfEventAction(const G4Event* anEvent);

  private:
    G4int hitsCollectionID;
    mintDataFile* dataFile;
    mintPrimaryGeneratorAction* mintPGA;
};

#endif
