#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <fstream>

#include "TCanvas.h"
#include "TH1D.h"


using namespace std;

void PrintUsage(){
  cout<<
    "This program draws" << endl <<
    "(1) histograms of TDC" << endl << 
    "(2) histograms of ADC" << endl <<
    "(3) 2Dhistograms of TDC and ADC" << endl <<
    "Please make the order of data columns to be TDC1 TDC2 TDC3 ..... TDCn ADC1 ADC2 ADC3.... ADCn" << endl <<
    "Input data file to process \t: -f filename1 -f filename2 -f filename3.... " << endl <<
    "To Set the number of data colunms \t : -n `# of data colunms`" << endl;
}

int main(int argc, char *argv[])
{
  vector<TString> files;
  Int_t nCols = 0;
  
  if(argc == 1)
  {
    PrintUsage();
    return 1;
  }
  else{
    files.reserve(argc-1);
    for(Int_t i = 1;i < argc;i++)
    {
      if(strcmp(argv[i], "-f")) files.push_back(TString(argv[i+1]));
      if(strcmp(argv[i], "-n")) nCols = atoi(argv[i+1]);
    }

  }
  return 1;
}
  

