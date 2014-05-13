#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4UIdirectory.hh"
#include "G4UImessenger.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "mintPrimaryGeneratorAction.hh"
#include "mintPrimaryGeneratorMessenger.hh"


mintPrimaryGeneratorMessenger::mintPrimaryGeneratorMessenger
(mintPrimaryGeneratorAction* mintGun, G4RunManager* runManagerPointer)
:mintPGA(mintGun), runManager(runManagerPointer)
{
  amdDirectory = new G4UIdirectory("/amd/");
  amdDirectory -> SetGuidance("Commands for using AMD data");

  useAMDData = new G4UIcmdWithAnInteger("/amd/useAMDData", this);
  useAMDData -> SetGuidance("Choose whether you are going to use AMD data (1:use, 0(default):don't use)");
  useAMDData -> SetParameterName("useAMDData", true);
  useAMDData -> SetDefaultValue(0);
  useAMDData -> AvailableForStates(G4State_PreInit, G4State_Idle);


  eventNumber = new G4UIcmdWithAnInteger("/amd/useEventNumber", this);
  eventNumber -> SetGuidance("Select event number (1 ~ 2010, default=1)");
  eventNumber -> SetParameterName("eventNumber", true);
  eventNumber -> SetDefaultValue(1);
  eventNumber -> AvailableForStates(G4State_PreInit, G4State_Idle);

  run = new G4UIcmdWithoutParameter("/amd/run", this);
  run -> SetGuidance("Run selected event");
  run -> AvailableForStates(G4State_PreInit, G4State_Idle);
}

mintPrimaryGeneratorMessenger::~mintPrimaryGeneratorMessenger()
{
  delete amdDirectory;
  delete run;
  delete eventNumber;
  delete useAMDData;
}

void mintPrimaryGeneratorMessenger::SetNewValue(G4UIcommand* command, G4String value)
{
  if(command==useAMDData) mintPGA -> PrepareBeam();
  else if(command==eventNumber)
  {
    mintPGA -> SetEventNumber(eventNumber -> GetNewIntValue(value));
    mintPGA -> PrepareBeam();
  }
  else if(command==run) runManager -> BeamOn(mintPGA->GetNumberOfTracks());
}
