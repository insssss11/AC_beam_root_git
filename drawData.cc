// written by Hyunmin Yang in HANUL of Prof Ahn.

#include <iostream>
#include <fstream>



Int_t drawData(const char *file)
{
  TString fileName(file);
  TString textFileName(fileName + ".txt");
  TString rootFileName(fileName + ".root");
  
  std::ifstream textFileIn(textFileName.Data(), ios::in);
  if(!textFileIn.is_open())
  {
    std::cout << "Cannot find " + textFileName + "!" << std::endl;
    return -1;
  }

  // TFile rootFileIn(rootFileName, "RECREATE");
  
  // histogram definition
  TH1S *hist1[5];
  TH1S *hist2[5];
  TH2S *hist3[5];
  
  for(Int_t i = 0;i < 4;i++)// channel 1 ~ 4 is trigger
  {
    TString numString = TString::Itoa(i+1,10);
    hist1[i] = new TH1S("", "ADC from trig" + numString, 100, 0., 4096.);
    hist2[i] = new TH1S("", "TDC from trig" + numString, 100, 0., 4096.);
    hist3[i] = new TH2S("", "ADC vs TDC of trig " + numString, 100, 0., 4096., 100, 0., 4096.);
  }
 
  hist1[4] = new TH1S("", "ADC from AC detector", 100, 0., 4096.);// channel 5 is AC detector
  hist2[4] = new TH1S("", "TDC from AC detector", 100, 0., 4096.);
  hist3[4] = new TH2S("", "ADC vs TDC of AC detector", 100, 0., 4096., 100, 0., 4096.);

  // setting axis properties
  for(Int_t i = 0;i < 5;i++)
  {
    hist1[i]->GetXaxis()->SetTitle("ch");
    hist2[i]->GetXaxis()->SetTitle("ch");
    hist3[i]->GetXaxis()->SetTitle("ADC ch");
    
    hist1[i]->GetYaxis()->SetTitle("count");
    hist2[i]->GetYaxis()->SetTitle("count");
    hist3[i]->GetYaxis()->SetTitle("TDC ch");
  }
    
  // tree and branches definition
  TTree *tree = new TTree("tree", "ACtest");
  
  Int_t nev = 0;
  Short_t data[10] = {0};
  Short_t adc_raw[5] = {0};
  Short_t tdc_raw[5] = {0};
  
  tree->Branch("nev", &nev, "I");
  tree->Branch("ADC", data, "S[5]");
  tree->Branch("TDC", data + 5,"S[5]");
  
  // reading text file
  while(!textFileIn.eof())
  {
    nev++;
    
    for(Int_t i = 0;i < 10;i++)
    {
      textFileIn >> data[i];
    }
    std::cout << data[0] << " " << data[1] << " " << data[2] << " " << data[3] << " " << data[4] <<  std::endl;
    
    for(Int_t i = 0;i < 5;i++)
    {
      hist1[i]->Fill(data[i]);
      hist2[i]->Fill(data[i+5]);
      hist3[i]->Fill(data[i], data[i+5]);
    }
    tree->Fill();
  }

  // rootFileIn.Write();
  // rootFileIn.Close();
  
  TCanvas *c1 = new TCanvas("c1", fileName, 900, 600);
  TCanvas *c2 = new TCanvas("c2", fileName, 900, 600);
  TCanvas *c3 = new TCanvas("c3", fileName, 900, 600);

  c1->Divide(3, 2);
  c2->Divide(3, 2);
  c3->Divide(3, 2);

  for(Int_t i = 0;i < 5;i++)
  {
    c1->cd(i+1);
    hist1[i]->Draw();
    c2->cd(i+1);
    hist2[i]->Draw();
    c3->cd(i+1);
    hist3[i]->Draw();
  }

  std::cout << "The # of events : " << nev << std::endl;
  return 1;
}
  

