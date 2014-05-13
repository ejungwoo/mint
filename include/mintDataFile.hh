#ifndef mintDataFile_hh
#define mintDataFile_hh 1

#include <TFile.h>
#include <TTree.h>

class TFile;
class TTree;

class mintDataFile
{
  public:
    mintDataFile();
    ~mintDataFile();
    
    void Fill(double preX,
              double preY,
              double preZ,
              double theta,
              int    pID,
              int    parentID,
              double time,
              double edep);

    void SetTrackNumber(int val)         { trackNumber = val; }

  private:
    void SetBranch();

    double preX, preY, preZ, edep, theta, time;
    int    parentID, pID;
    int    trackNumber;

    TFile* dataFile;
    TTree* dataTree;
};

#endif
