#include "TMath.h"

using namespace TMath;

const Double_t M_PION = 139.57018; // MeV/c
const Double_t RINDEX = 1.05;
const Double_t WIDTH  = 60e-3; // 60 mm
const Double_t ANGLE  = 50.*DegToRad(); // radian
const Double_t L_MIN  = 350e-9;
const Double_t L_MAX  = 600e-9;

Double_t GetBeta(Double_t p) // unit is MeV/c
{
  return Sqrt(1. - 1./((p*p)/(M_PION*M_PION) + 1.));
}

Int_t calPhotons(Double_t p)
{
  Double_t beta = GetBeta(p);
  Double_t dz   = WIDTH/Cos(ANGLE);

  Int_t nPhotons = (Int_t)2*Pi()*(1. - 1./(RINDEX*RINDEX*beta*beta))*(1./L_MIN - 1./L_MAX)*dz/137;
  std::cout << "The unit of input momentum is MeV/c." << std::endl;
  
  std::cout << "beta \t\t: " << beta << std::endl;
  std::cout << "dz \t\t: " << dz*1e3 << " mm" << std::endl;
  std::cout << "The # of photons : " << nPhotons << std::endl;

  return 1;
}

