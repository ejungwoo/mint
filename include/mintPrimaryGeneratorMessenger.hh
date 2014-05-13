#ifndef mintPrimaryGeneratorMessenger_hh
#define mintPrimaryGeneratorMessenger_hh 1

#include "G4RunManager.hh"
#include "G4UIdirectory.hh"
#include "G4UImessenger.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithoutParameter.hh"

class G4RunManager;
class mintPrimaryGeneratorAction;
class G4UIcmdWithoutParameter;
class G4UIcmdWithAnInteger;
class G4UIdirectory;

class mintPrimaryGeneratorMessenger: public G4UImessenger
{
  public:
    mintPrimaryGeneratorMessenger(mintPrimaryGeneratorAction*, G4RunManager*);
    ~mintPrimaryGeneratorMessenger();

    void SetNewValue(G4UIcommand*, G4String);

  private:
    mintPrimaryGeneratorAction* mintPGA;
    G4RunManager* runManager;

    G4UIdirectory* amdDirectory;
    G4UIcmdWithoutParameter* run;
    G4UIcmdWithAnInteger*    useAMDData;
    G4UIcmdWithAnInteger*    eventNumber;
};
#endif
