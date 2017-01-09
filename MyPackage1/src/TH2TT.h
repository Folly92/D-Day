#ifndef TH2TT_H
#define TH2TT_H

#include <string>
#include <map>
#include <TH2.h>

class TH2TT : public TH2D {
 public:
    TH2TT(const char *name, const char *title);
    virtual ~TH2TT();
    
    virtual Int_t Fill(Double_t) { return -1; };
    virtual Int_t Fill(const char*, Double_t) { return -1; }
    virtual Int_t Fill(Double_t x, Double_t y);
    virtual Int_t Fill(Double_t x, Double_t y, Double_t w);
    virtual Int_t Fill(Double_t x, const char *namey, Double_t w);
    virtual Int_t Fill(const char *namex, Double_t y, Double_t w);
    virtual Int_t Fill(const char *namex, const char *namey, Double_t w);
    virtual TH1D* ProjectionX(double min);
    // virtual void SetBinContent2(Double_t x, Double_t y, Double_t content);
};

#endif //TH2TT_H
