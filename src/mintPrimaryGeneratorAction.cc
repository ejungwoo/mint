#include "mintPrimaryGeneratorAction.hh"

#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleGun.hh"
#include "G4Event.hh"
#include "G4IonTable.hh"
#include "G4UnitsTable.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"

#include <iostream>

mintPrimaryGeneratorAction::mintPrimaryGeneratorAction(G4RunManager* runManagerPointer, mintDataFile* mintDFPointer)
:runManager(runManagerPointer), mintDF(mintDFPointer), gunPosition(G4ThreeVector()), eventNumber(1) 
{
  particleGun = new G4ParticleGun;
  mintPGM = new mintPrimaryGeneratorMessenger(this, runManager);

  PrepareParticles();
  SetSingleParticleBeam();
}

mintPrimaryGeneratorAction::~mintPrimaryGeneratorAction()
{
  delete particleGun;
  delete mintPGM;
  //delete event;
}

void mintPrimaryGeneratorAction::PrepareBeam()
{
  if(event) event -> SelectEvent(eventNumber);
  else      event = new mintAMDEvent(this, eventNumber);
  trackNumber=0;
}

void mintPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  if(event) SetAMDEvent();
  mintDF -> SetTrackNumber(trackNumber);

  //std::cout << trackNumber << ": " << beamParticle -> GetParticleName() << ", " << beamParticle -> GetPDGEncoding() << std::endl;
  particleGun -> GeneratePrimaryVertex(anEvent);
}

void mintPrimaryGeneratorAction::SetAMDEvent()
{
  event -> GetBeam(trackNumber);

  //momentum
  G4ThreeVector momentum(trackPx*MeV, trackPy*MeV, trackPz*MeV);
  //momentum magnitude
  momentumMagnitude = sqrt(momentum.x()*momentum.x()
                          +momentum.y()*momentum.y()
                          +momentum.z()*momentum.z());
  //momentum direction
  momentumDirection = G4ThreeVector(momentum.x()/momentumMagnitude
                                   ,momentum.y()/momentumMagnitude
                                   ,momentum.z()/momentumMagnitude);
  //particle: GetIon([atomic number],[atomic mass],[excitation energy=0: ground state])
  if(trackZ==0&&trackZ+trackN==1)      beamParticle = particleTable -> FindParticle("neutron");
  else if(trackZ==1&&trackZ+trackN==1) beamParticle = particleTable -> FindParticle("proton");
  else                                 beamParticle = particleTable -> GetIon(trackZ, trackZ+trackN, 0);

  //kinetic energy 
  SetKineticEnergy();

  particleGun -> SetParticlePosition(gunPosition);
  particleGun -> SetParticleDefinition(beamParticle);
  particleGun -> SetParticleMomentumDirection(momentumDirection);
  particleGun -> SetParticleEnergy(kineticEnergy);
}

void mintPrimaryGeneratorAction::PrepareParticles()
{
  particleTable = G4ParticleTable::GetParticleTable();
}

void mintPrimaryGeneratorAction::SetKineticEnergy()
{
  G4double protonMass = 938.272; // MeV/c2
  G4double neutronMass = 939.565; // MeV/c2
  G4double mass = protonMass*trackZ + neutronMass*trackN;
  kineticEnergy = sqrt(momentumMagnitude*momentumMagnitude+mass*mass) - mass;
}

void mintPrimaryGeneratorAction::SetSingleParticleBeam()
{
  beamParticle = particleTable -> FindParticle("neutron");
  momentumDirection = G4ThreeVector(0,0,1);
  kineticEnergy = 20*MeV;

  particleGun -> SetParticlePosition(gunPosition);
  particleGun -> SetParticleDefinition(beamParticle);
  particleGun -> SetParticleMomentumDirection(momentumDirection);
  particleGun -> SetParticleEnergy(kineticEnergy);
}


void mintPrimaryGeneratorAction::SetBeam(int N, int Z, double pX, double pY, double pZ)
{
  trackN = N;
  trackZ = Z;
  trackPx = pX;
  trackPy = pY;
  trackPz = pZ;
}

void mintPrimaryGeneratorAction::EndOfTrack()
{
  trackNumber++;
}
