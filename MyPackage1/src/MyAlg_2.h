#ifndef MYPACKAGE1_MYALG_2_H
#define MYPACKAGE1_MYALG_2_H 1

#include <vector>
#include "AthenaBaseComps/AthAlgorithm.h"
#include "GaudiKernel/ToolHandle.h" //included under assumption you'll want to use some tools! Remove if you don't!

#include "GaudiKernel/ITHistSvc.h"

#include "TH1.h"
#include "TH2.h"
#include "TH2TT.h"

class MyAlg_2: public ::AthAlgorithm { 
 public: 
  MyAlg_2( const std::string& name, ISvcLocator* pSvcLocator );
  virtual ~MyAlg_2(); 

  virtual StatusCode  initialize();
  virtual StatusCode  execute();
  virtual StatusCode  finalize();

 private: 
 TH1F * pulseShape1[2000];
}; 

#endif //> !MYPACKAGE1_MYALG_2_H
