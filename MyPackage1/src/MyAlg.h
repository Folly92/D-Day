#ifndef MYPACKAGE1_MYALG_H
#define MYPACKAGE1_MYALG_H 1

#include <vector>
#include "AthenaBaseComps/AthAlgorithm.h"
#include "GaudiKernel/ToolHandle.h" //included under assumption you'll want to use some tools! Remove if you don't!

#include "GaudiKernel/ITHistSvc.h"
#include <string>
#include <fstream>
#include <stdexcept>
#include <map>
#include <utility>
#include <iostream>
#include <iomanip>
#include <string.h>
#include "TH1.h"
#include "TH2.h"
#include "TH2TT.h"
#include "TProfile.h"
//#include "TCanvas.h"

class MyAlg: public ::AthAlgorithm { 
 public: 
  MyAlg( const std::string& name, ISvcLocator* pSvcLocator );
  virtual ~MyAlg(); 

  virtual StatusCode  initialize();
  virtual StatusCode  execute();
  virtual StatusCode  finalize();

 private: 
//7168->7168
//1800->2236
  //Histograms
  //TCanvas * c1;
  TH1F * pulseShape[2000];
  //TH1F * pulseNewShape[2800];
  //TH2F * profile[7168];
  TH1F * calibration[7168];
  TH1F * calibration2[7168];
  TH1F * spectrum[7168];
  TH1F * spectrum_0[7168];
  TH1F * spectrum_1[7168];
  //TH1F * peak[7168];
  TH2F * TH2Feta[66][15];
  TH2F * ADChisto[7168][15];
  TH2F * TH2Fhisto[15];
  //TH2F * TH2Fcheck[7168][15];
  //TH2F * TH2Fcheck2[7168][15];
  TH2F * mvsm[7168];
  TH2F * corrETvsPeak[7168];
  TH1F * peakFinder[7168];
  TH1F * saturation[7168];
  TH1F * PSE[7168];
  TH2TT * numberStep_0;
  TH2TT * numberStep_1;

  //TH1F * WrongEvent[7168];
  TH2F * S;
  TH2F * S_2;
  TH2F * S_1;
  TH2F * S_wrong;
  TH2F * S_2_wrong;
  TH2F * S_1_wrong;
  TH2F * l_wrong;
  TH2F * h_l_wrong;
  TH2F * h_wrong;
  TH2TT * lE_P_Map[4];
  TH2TT * lE_P_Map_NB[4];
  TH2TT * lE_P_Map_NB_NS[4];
  
  TH2TT * Step_ET[15][2];
  TH2TT * Step_ADC[15][2];
  TH2TT * Step_PSE[15][2];
  TH2TT * SatPeak[15][2]; 
  TH2TT * Step_SatADC[15][2];
  TH2TT * Step_Lut_jep[15][2];
  TH2TT * Step_RHL[15][2][3];
  TH2TT * Step_BeforeP[15][2];
  TH2TT * Step_Check[15][2];
  TH2TT * Step_event[15][2];
  TH2TT * Step_secondSatADC[15][2];
  TH2TT * Step_secondET[15][2];
  TH2TT * fail[15][2];
  TH2TT * result[15][2];
  TH2TT * logic[15][2];
  TH2TT * logic_wrong[15][2];
  //TH1D * Calc[7168][30];
  //TH1F * TotalWrongEvent;


  //int m_TTcounter;

 //std::vector<int> m_sum;
 //std::vector<float> m_bcid;
 //std::vector<float> m_sumBCID;
 //std::vector<int> m_count1;
 //std::vector<int> m_count2;
 //std::vector<int> m_adc_test;
 //std::vector<int> m_max;
 //std::vector<int> m_maxpos;
 //std::vector<int> m_broken;
 //std::vector<unsigned int> pulse;
 //std::vector<int> m_sat;
 //std::vector<float> caloET;
 //std::vector<int> m_average;
 //std::vector<int> m_average1;
 //std::vector<int> m_average2;
 //std::vector<int> m_divide;
 //std::vector<float> m_phi;
 //std::vector<float> m_eta;
 //std::vector<int> m_brokenttvec;
 //std::vector<int> m_layer;
 //std::vector<int> m_step;
std::map<std::string,int> m_low_t;
std::map<std::string,int> m_high_t;  

 
 // new way


 int * m_adc_test;
 float * m_caloET_test;
 int * m_sum;
 int * m_bcid;
 float * m_sumBCID;
 int * m_count1;
 int * m_count2;
 int * m_max;
 int * m_maxpos;
 int * m_broken;
 int * pulse;
 int * m_sat;
 int * m_sat_odd;
 int * m_distance;
 int * m_distance_odd;
 float * caloET;
 int * m_average;
 int * m_average1;
 int * m_average2;
 int * m_divide;
 float * m_phi;
 float * m_eta;
 int * m_brokenttvec;
 int * m_layer;
 int * m_step;
 int * m_lut_jep;
 int * failing;
 int * m_rhl0;
 int * m_rhl1;
 int * m_rhl2;
 int * m_max_prime;
 float * etaslice;
 //std::string * x[3][8193];
 //double * sigma[7168][30];
 //double * mean[7168][30];
 //unsigned int * events_step[7168][30]; 

 unsigned int m_lay;
 unsigned int events;
 int number_TT;
 int number_ADC;
 int central;
 unsigned int number_brokentt;



}; 

#endif //> !MYPACKAGE1_MYALG_H[2236]
