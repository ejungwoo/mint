#include "mintAMDEvent.hh"
#include "mintPrimaryGeneratorAction.hh"

#include <TFile.h>
#include <TTree.h>

#include <sstream>

mintAMDEvent::mintAMDEvent(mintPrimaryGeneratorAction* mintPGAPointer, G4int eventNumberPointer)
:mintPGA(mintPGAPointer), eventNumber(int(eventNumberPointer))
{
  amdData = new TFile("data/AMD.root","read");
  SelectEvent(eventNumber);
}

mintAMDEvent::~mintAMDEvent()
{
  delete amdData;
  delete eventTree;
}

void mintAMDEvent::SelectEvent(int eventNumber)
{
  std::stringstream eventTreeName;
  eventTreeName << "event_" << eventNumber;

  //eventTree = (TTree*) amdData -> Get(eventTreeName);
  eventTree = (TTree*) amdData -> Get(Form("event_%d",eventNumber));
  eventTree -> SetBranchAddress("N", &N);
  eventTree -> SetBranchAddress("Z", &Z);
  eventTree -> SetBranchAddress("pX", &pX);
  eventTree -> SetBranchAddress("pY", &pY);
  eventTree -> SetBranchAddress("pZ", &pZ);

  numberOfTracks = eventTree -> GetEntries();
  mintPGA -> SetNumberOfTracks(numberOfTracks);
}

void mintAMDEvent::GetBeam(int trackNumber)
{
  eventTree -> GetEntry(trackNumber);
  mintPGA -> SetBeam(N, Z, pX, pY, pZ);
}
