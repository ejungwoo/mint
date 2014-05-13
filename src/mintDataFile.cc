#include <mintDataFile.hh>
#include <iostream>

mintDataFile::mintDataFile()
{
  dataFile = new TFile("data/rawData.root","recreate");
  dataTree = new TTree("data","");
  SetBranch();
}

void mintDataFile::SetBranch()
{
  dataTree -> Branch("x",&preX,"x/D");
  dataTree -> Branch("y",&preY,"y/D");
  dataTree -> Branch("z",&preZ,"z/D");
  dataTree -> Branch("theta",&theta,"theta/D");
  dataTree -> Branch("pID",&pID,"pID/I");
  dataTree -> Branch("parentID",&parentID,"parentID/I");
  dataTree -> Branch("edep",&edep,"edep/D");
  dataTree -> Branch("time",&time,"time/D");
  dataTree -> Branch("trackNumber",&trackNumber,"trackNumber/I");
  //dataTree -> Branch("pID",&particleID,"pID/i");
}

mintDataFile::~mintDataFile()
{
  dataFile -> cd();
  dataTree -> Write();

  std::cout << "rawData.root is created!" << std::endl;

  delete dataTree;
  delete dataFile;
}

void mintDataFile::Fill(double preX_val,
                        double preY_val,
                        double preZ_val,
                        double theta_val,
                        int    parentID_val,
                        int    pID_val,
                        double time_val,
                        double edep_val)
{
  preX     = preX_val;
  preY     = preY_val;
  preZ     = preZ_val;
  theta    = theta_val;
  pID      = pID_val;
  parentID = parentID_val;
  time     = time_val;
  edep     = edep_val;

  dataTree -> Fill();
}
