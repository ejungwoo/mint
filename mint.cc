#include "mintDetectorConstruction.hh"
#include "mintPrimaryGeneratorAction.hh"
#include "mintEventAction.hh"
#include "mintField.hh"
#include "A01PhysicsList.hh"

#include "G4RunManager.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"

int main(int argc, char ** argv)
{
  mintDataFile *mintDF = new mintDataFile();

  //Run
  G4RunManager *runManager = new G4RunManager();

  mintDetectorConstruction* mintDC = new mintDetectorConstruction();
  runManager -> SetUserInitialization(mintDC);

  A01PhysicsList* physicsList = new A01PhysicsList();
  runManager -> SetUserInitialization(physicsList);

  mintPrimaryGeneratorAction* mintPGA = new mintPrimaryGeneratorAction(runManager, mintDF);
  runManager -> SetUserAction(mintPGA);

  mintEventAction* mintEA = new mintEventAction(mintDF, mintPGA);
  runManager -> SetUserAction(mintEA);

  runManager -> Initialize();

  //Field
  G4FieldManager* fieldManager;
  fieldManager = G4TransportationManager::GetTransportationManager() -> GetFieldManager();
  mintField* field = new mintField(fieldManager, mintDC);
  //field -> SetLocalField();
  field -> SetGlobalField();
  
  //Visual
  G4VisManager* visManager = new G4VisExecutive();
  visManager -> Initialize();

  // for macro files
  if(argc==1)
  {
    G4UIsession* session = new G4UIterminal(new G4UItcsh);
    session -> SessionStart();
    delete session;
  }

  else
  {
    G4String command = "/control/execute ";
    G4String fileName = argv[1];

    G4UImanager* UI = G4UImanager::GetUIpointer();
    UI -> ApplyCommand(command + fileName);

    G4UIsession* session = new G4UIterminal(new G4UItcsh);
    session -> SessionStart();
    delete session;
  }

  delete runManager;
  delete visManager;
  delete mintDF;

  return 0;
}
