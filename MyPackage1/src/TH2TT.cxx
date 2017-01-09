#include "TH2TT.h"
#include "TMath.h"

// -----------------------------------------------------------------------------
//                                    TH2TT
// -----------------------------------------------------------------------------
TH2TT::TH2TT(const char *name, const char *title) :
  TH2D(name, title, 1, 0., 1., 1, 0., 1.)
{
    double TTEtaBins[67];
    double TTPhiBins[65];
    double BinContent(0.);


    TTEtaBins[0]=-4.9;
    TTEtaBins[1]=-4.475;
    TTEtaBins[2]=-4.050;
    TTEtaBins[3]=-3.625;
    TTEtaBins[4]=-3.2;

    BinContent=-3.1;
    for (int i=5; i<8; i++) {
	TTEtaBins[i]=BinContent;
	BinContent=BinContent+0.2;
    }
    for (int i=8; i<58; i++) {
	TTEtaBins[i]=BinContent;
	BinContent=BinContent+0.1;
    }
    for (int i=58; i<62; i++) {
	TTEtaBins[i]=BinContent;
	BinContent=BinContent+0.2;
    }
    
    TTEtaBins[62]=3.2;
    TTEtaBins[63]=3.625;
    TTEtaBins[64]=4.050;
    TTEtaBins[65]=4.475;
    TTEtaBins[66]=4.9;
    
    BinContent=0;
    for (int i=0; i<65; i++) {
	TTPhiBins[i]=BinContent;
	BinContent=BinContent+2*TMath::Pi()/64;
    }
    
    SetBins(66, TTEtaBins, 64, TTPhiBins);
	 TH2D::SetOption("COLZ");
}

TH2TT::~TH2TT()
{
}

Int_t TH2TT::Fill(Double_t x, Double_t y)
{
    return Fill(x, y, 1.);
}

Int_t TH2TT::Fill(Double_t x, Double_t y, Double_t w)
{
    if(x < -3.2 || x >= 3.2) {
        // fcal
        Int_t bn = fYaxis.FindBin(y) - 1;
        for(int i = 1; i <= 4; ++i) {
            TH2D::Fill(x, fYaxis.GetBinCenter((bn/4)*4 + i), w);
        }
        return bn;
    } else if(x < -2.5 || x >= 2.5) {
        // endcap
        Int_t bn = fYaxis.FindBin(y) - 1;
        for(int i = 1; i <= 2; ++i) {
            TH2D::Fill(x, fYaxis.GetBinCenter((bn/2)*2 + i), w);
        }
        return bn;
    } else {
        // barrel
        return TH2D::Fill(x, y, w);
    }
//    return TH2D::Fill(x, y, w);
}

TH1D * TH2TT::ProjectionX(double min) {
   TH1D * result = TH2D::ProjectionX();
   Double_t bin[fXaxis.GetNbins()];
   for (Int_t x = 1; x <= (fXaxis.GetNbins()); x++)  {
      bin[x]=0;
      Int_t i=0;
      for (Int_t y = 1; y <= (fYaxis.GetNbins()); y++)  {
	 if (TH2D::GetBinContent(x, y) > min) {
	    bin[x]+=TH2D::GetBinContent(x, y);
	    i++;
	 }
      }
      if (i == 0)
	 result->SetBinContent(x, min);
      else
	 result->SetBinContent(x, bin[x]/i);
   }
   return result;
}


// void TH2TT::SetBinContent2(Double_t x, Double_t y, Double_t content) {
//     Int_t bx = fXaxis.FindBin(x);
//     if(x < -3.2 || x >= 3.2) {
//         // fcal
//         Int_t by = fYaxis.FindBin(y) - 1;
//         for(int i = 1; i <= 4; ++i) {
//             TH2D::SetBinContent(bx, (by/4)*4 + i, content);
//         }
//     } else if(x < -2.5 || x >= 2.5) {
//         // endcap
//         Int_t by = fYaxis.FindBin(y) - 1;
//         for(int i = 1; i <= 2; ++i) {
//             TH2D::SetBinContent(bx, (by/2)*2 + i, content);
//         }
//     } else {
//         // barrel
//         Int_t by = fYaxis.FindBin(y);
//         TH2D::Fill(bx, by, content);
//     }
// }

Int_t TH2TT::Fill(Double_t x, const char *namey, Double_t w) {
   return Fill(x, fYaxis.GetBinCenter(fYaxis.FindBin(namey)), w);
}

Int_t TH2TT::Fill(const char *namex, Double_t y, Double_t w) {
   return Fill(fXaxis.GetBinCenter(fXaxis.FindBin(namex)), y, w);
}

Int_t TH2TT::Fill(const char *namex, const char *namey, Double_t w) {
   return Fill(fXaxis.GetBinCenter(fXaxis.FindBin(namex)), 
               fYaxis.GetBinCenter(fYaxis.FindBin(namey)),
               w);
}
