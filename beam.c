void beam(int runno=1){

  char infile[256];
  char outfile[256];

  sprintf(infile,"bm%02d.txt",runno);
  sprintf(outfile,"bm%02d.root",runno);
  
  std::ifstream inf1(infile);
  TFile * fout=new TFile(TString("tree/") + outfile,"recreate");
  int data[10];
  TTree * tree = new TTree("tree","title");

  tree->Branch(TString::Format("bm0%d", runno), data, "ADC[5]/I:TDC[5]");


  while(true){
    inf1 >> data[0] >> data[1] >> data[2] >> data[3] >> data[4] >> data[5] >> data[6] >> data[7] >> data[8] >> data[9];
    if(inf1.eof())
      break;
    tree->Fill();
  }

  TCanvas *c1 = new TCanvas("ADC");
  TCanvas *c2 = new TCanvas("TDC");
  TCanvas *c3 = new TCanvas("ADCvsTDC");
  c1->Divide(3,2);
  c2->Divide(3,2);
  c3->Divide(3,2);

  for(Int_t i = 1;i <=5;i++)
  {
    c1->cd(i);
    tree->Draw(TString::Format("ADC[%d]", i-1));
    c2->cd(i);
    tree->Draw(TString::Format("TDC[%d]", i-1));
    c3->cd(i);
    tree->Draw(TString::Format("TDC[%d]:ADC[%d]", i-1, i-1));
  }


  fout->Write();
  inf1.close();
  fout->Close();
  delete fout;
}
