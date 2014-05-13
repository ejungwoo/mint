#ifndef mintAMDEvent_hh
#define mintAMDEvent_hh 1

#include <TFile.h>
#include <TTree.h>
#include "mintPrimaryGeneratorAction.hh"

class mintPrimaryGeneratorAction;

class mintAMDEvent
{
  public:
    mintAMDEvent(mintPrimaryGeneratorAction* mintPGA, G4int eventNumber);
    ~mintAMDEvent();

    void GetBeam(int trackNumber);
    void SelectEvent(int eventNumber);

  private:
    mintPrimaryGeneratorAction* mintPGA;

    int eventNumber;
    int numberOfTracks;

    int N, Z; 
    double pX, pY, pZ;
    
    TFile* amdData;
    TTree* eventTree;
};
#endif
