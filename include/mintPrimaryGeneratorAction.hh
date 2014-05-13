#ifndef mintPrimaryGeneratorAction_h
#define mintPrimaryGeneratorAction_h 1

#include "globals.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"

#include "mintAMDEvent.hh"
#include "mintDataFile.hh"
#include "mintPrimaryGeneratorMessenger.hh"

class G4ParticleGun;
class mintAMDEvent;
class mintDataFile;

class mintPrimaryGeneratorAction: public G4VUserPrimaryGeneratorAction
{
  public:
    mintPrimaryGeneratorAction(G4RunManager* runManagerPointer, mintDataFile* mitDFPointer);
    ~mintPrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event* anEvent);

    void SetBeam(int N, int Z, double pX, double pY, double pZ);
    void EndOfTrack();
    void PrepareBeam();

    void SetNumberOfTracks(G4int val) { numberOfTracks = val; }
    int  GetNumberOfTracks()          { return numberOfTracks; }
    void SetEventNumber(G4int val)    { eventNumber = val; }

  private:
    void PrepareParticles();
    void SetSingleParticleBeam();
    void SetAMDEvent();
    void SetKineticEnergy();

    G4RunManager* runManager;
    mintAMDEvent* event;

    G4ParticleGun* particleGun;

    mintDataFile* mintDF;
    mintPrimaryGeneratorMessenger* mintPGM;

    G4ParticleTable *particleTable;

    G4ThreeVector gunPosition;
    G4ParticleDefinition *beamParticle;
    G4ThreeVector momentumDirection;
    G4double kineticEnergy;

    G4double momentumMagnitude;

    G4int eventNumber;
    G4int numberOfTracks;
    G4int trackNumber;

    G4int trackN, trackZ;
    G4double trackPx, trackPy, trackPz;
};

#endif
