// MyPackage1 includes
#include "MyAlg_2.h"
#include <typeinfo>
#include "xAODEventInfo/EventInfo.h"
#include "xAODTrigL1Calo/TriggerTower.h"
#include "xAODTrigL1Calo/TriggerTowerContainer.h"

#include "TFile.h"
#include <map>
#include <utility>
#include <iostream>
#include <stdio.h>      
#include <stdlib.h>
#include <stdexcept>
#include <fstream>
#include <iomanip>
#include "TFile.h"
#include "TMath.h"
#include <string>
#include <vector>
#include "string.h"


MyAlg_2::MyAlg_2( const std::string& name, ISvcLocator* pSvcLocator ) : AthAlgorithm( name, pSvcLocator ){

  //declareProperty( "Property", m_nProperty ); //example property declaration

}


MyAlg_2::~MyAlg_2() {}


StatusCode MyAlg_2::initialize() {
  ATH_MSG_INFO ("Initializing " << name() << "...");

    ServiceHandle<ITHistSvc> histSvc("THistSvc",name());
  	CHECK( histSvc.retrieve() );

  	std::string name;
	std::string title;
 	std::string path;

  	for(unsigned int i=0;i<2000;i++){
    name = "pulseShape_"+std::to_string(i);
  	title = "PulseShape in tower 0x4120b01 (eta=2.0)";
  	path = "/file1/pulseShape1/"+name;
  	pulseShape1[i] = new TH1F(name.c_str(),title.c_str(),15,0.,15.);
	//pulseShape[i].SetName(name.c_str());
  	CHECK(histSvc->regHist(path.c_str(),pulseShape1[i]));
  	}
  return StatusCode::SUCCESS;
}

StatusCode MyAlg_2::finalize() {
  ATH_MSG_INFO ("Finalizing " << name() << "...");

  return StatusCode::SUCCESS;
}

StatusCode MyAlg_2::execute() {  
  ATH_MSG_DEBUG ("Executing " << name() << "...");

const xAOD::EventInfo* eventInfo = 0;  //initialize a pointer 
 CHECK( evtStore()->retrieve(eventInfo)); // pointer to event storegate



 const DataVector<xAOD::TriggerTower>* trigTowColl = 0; //initialize a pointer "trigTowColl" that points at the method TriggerTower(that produces a vector)
 CHECK( evtStore()->retrieve(trigTowColl,"xAODTriggerTowers")); //pointer to the container xAODTriggerTowers

 int n_tt = trigTowColl->size();
std::cout<<n_tt<<std::endl;
for(unsigned int j=0;j<(trigTowColl->at(0)->adc()).size();j++){
	//I'm filling the histogram bin to bin (17 bins) with the number of the correspondig adc, leaving empthy the two border bins (0 and 17)	
	for (unsigned int l=0;l<(trigTowColl->at(0)->adc()).at(j);l++){		
		pulseShape1[eventInfo->eventNumber()]->Fill(j);
		}	
	}

  return StatusCode::SUCCESS;
}


