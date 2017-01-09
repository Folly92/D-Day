// MyPackage1 includes
#include "MyAlg.h"
#include <typeinfo>
#include "xAODEventInfo/EventInfo.h"
#include "xAODTrigL1Calo/TriggerTower.h"
#include "xAODTrigL1Calo/TriggerTowerContainer.h"

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
#include "TObject.h"
//#include "TCanvas.h"

MyAlg::MyAlg( const std::string& name, ISvcLocator* pSvcLocator ): AthAlgorithm( name, pSvcLocator )
 //, m_adc_test(2048 , 64) 
 //, m_sum(2048 , 0) 
 //, m_bcid(2048 , 0) 
 //, m_sumBCID(2048 , 0) 
 //, m_count1(2048 , 1) 
 //, m_count2(2048 , 1) 
 //, m_max(2048, 0) 
 //, m_maxpos(2048,0) 
 //, m_sat(2048,0) 
 //, m_broken(2048,1) 
 //, pulse(5,0)
 //, caloET(2048,0)
 //, m_layer(2048)
 //, m_average(2048,0)
 //, m_average1(2048,0)
 //, m_average2(2048,0)
 //, m_phi(2048)
 //, m_eta(2048)
 //, m_divide(2048,1)
 //, m_brokenttvec(132)
 //, m_step(2048,0)
//, m_low_t
//, m_high_t  

 
{

//declareProperty( "runShapes", m_runShapes ); //example property declaration
declareProperty( "m_low_t", m_low_t );
declareProperty( "m_high_t", m_high_t );
}


MyAlg::~MyAlg() {}


StatusCode MyAlg::initialize() {
  ATH_MSG_INFO ("Initializing " << name() << "...");

  //Get histogram service

  ServiceHandle<ITHistSvc> histSvc("THistSvc",name());
  CHECK( histSvc.retrieve() );


    events = 2000;
	//events = 1800;
	number_TT = 7168;
	//number_TT = 7168 ;
	number_ADC= 15 ;
	//number_ADC= 7 ;
	central=7;

	number_brokentt = 132;

 	m_adc_test = new int[number_TT];
	m_caloET_test = new float[number_TT];
	m_sum = new int[number_TT];	
	m_bcid = new int[number_TT];
	m_sumBCID = new float[number_TT];
	m_count1 = new int[number_TT];	
	m_count2 = new int[number_TT];
	m_max = new int[number_TT];
	m_maxpos = new int[number_TT];
	m_sat = new int[number_TT];
	m_sat_odd = new int[number_TT];
	m_distance = new int[number_TT];
	m_distance_odd = new int[number_TT];
	pulse = new int[number_ADC];
	m_broken = new int[number_TT];
	caloET = new float[number_TT];	
	m_average = new int[number_TT];
	m_average1 = new int[number_TT];
	m_average2 = new int[number_TT];
	m_layer = new int[number_TT];
	m_phi = new float[number_TT];
	m_eta = new float[number_TT];
	m_brokenttvec = new int[number_brokentt];
	m_step = new int[number_TT];
	m_divide = new int[number_TT]; 
	m_lut_jep = new int[number_TT];
	m_rhl0 = new int[number_TT]; 
	m_rhl1 = new int[number_TT]; 
	m_rhl2 = new int[number_TT]; 
	m_max_prime = new int[number_TT];
	failing = new int[number_TT];
	etaslice = new float[66];
	
std::cout<<"lol"<<std::endl;  
	/*
	for (int i = 0; i < number_TT; i++){
		for (int j = 0 ; j < 30 ; j++){
			sigma[i][j] = new double;
			mean[i][j] = new double;
			events_step[i][j] = new unsigned int;
			*sigma[i][j]=0;
			*mean[i][j]=0;
			*events_step[i][j]=0;
		}
	
	}
	*/
	for (int i = 0; i<number_ADC; i++){
		pulse[i]=0;
	}

	for (int i = 0; i<66;i++){
		etaslice[i]=0;
	} 
	

	for (int i = 0; i < number_TT ;i++ ) {

		m_adc_test[i]=64;
		m_sum[i]=0;
		m_bcid[i]=0.;
		m_sumBCID[i] = 0.;
		m_count1[i]=0;
		m_count2[i]=1;
		m_max[i]=0;
		m_maxpos[i]=0;
		m_broken[i]=1;
		failing[i]=0;
		m_sat[i]=0;
		m_sat_odd[i]=0;
		caloET[i]=0;
		m_average[i]=0;
		m_average1[i]=0;
		m_average2[i]=0;
		m_divide[i]=1;
		m_step[i]=0;
		m_distance[i]=0;
		m_distance_odd[i]=0;

		m_caloET_test[i]=7.5;

	}
		
 	std::string name;
	std::string title;
 	std::string path;
	/*
	FILE *brokentt;
	brokentt = fopen("brokentt_294593_LAR.txt","r");
	for (int i = 0;i < number_brokentt; i++){
			
			fscanf(brokentt,"%d", &m_brokenttvec[i]);
			//std::cout<<i<<std::endl;
		}
	fclose(brokentt);
	*/

	/*
  	name = "TotalWrongEvent";
  	title = "TotalWrongEvent";
  	path = "/file1/TotalWrongEvent";
  	TotalWrongEvent = new TH1F(name.c_str(),title.c_str(),1800,0.,1800.); //1800->2236
  	CHECK(histSvc->regHist(path.c_str(),TotalWrongEvent));	
	*/

  for(unsigned int i=0;i<events;i++){  //->1800->2236
	
  	name = "pulseShape_"+std::to_string(i);
  	title = "PulseShape in event "+std::to_string(i);
  	path = "/file1/pulseShape/"+name;
  	pulseShape[i] = new TH1F(name.c_str(),title.c_str(),15,0.,15.);
	//pulseShape[i].SetName(name.c_str());
  	CHECK(histSvc->regHist(path.c_str(),pulseShape[i]));
	/*
	name = "pulseNewShape_"+std::to_string(i);
  	title = "PulseShape in event "+std::to_string(i);
  	path = "/file1/pulseNewShape/"+name;
  	pulseNewShape[i] = new TH1F(name.c_str(),title.c_str(),5,0.,5.);
  	CHECK(histSvc->regHist(path.c_str(),pulseNewShape[i]));
	
 	//TH2F of the shape
	name = "TH2F_evt_"+std::to_string(i);
  	title = "TH2F of pulseShape in event "+std::to_string(i);
  	path = "/file1/TH2Fpulse/"+name;
  	profile[i] = new TH2F(name.c_str(),title.c_str(),5,0.,5.,1200,0.,1200.);
  	CHECK(histSvc->regHist(path.c_str(),profile[i]));
	*/
      	
  }
	std::cout<<"lol"<<std::endl;

  	name = "numberStep_0";
    	title = "numberStep_0";
    	path = "/file1/numberStep_0/"+name;
    	numberStep_0 = new TH2TT(name.c_str(),title.c_str());
    	CHECK(histSvc->regHist(path.c_str(),numberStep_0));
  	
	name = "numberStep_1";
    	title = "numberStep_1";
    	path = "/file1/numberStep_1/"+name;
    	numberStep_1 = new TH2TT(name.c_str(),title.c_str());
    	CHECK(histSvc->regHist(path.c_str(),numberStep_1));

  for( int i=0;i<number_TT;i++){ 	//2048->7168

    /*
	for ( int g=0;g<number_brokentt;g++){
		//if i = number of broken tt 
		if (i==m_brokenttvec[g]){
			m_broken[i]=0;
			}
    		}
        */
	/*
	name = "WrongEvent_"+std::to_string(i);
    	title = " Wrong Event "+std::to_string(i);
    	path = "/file1/WrongEvent/"+name;
    	WrongEvent[i] = new TH1F(name.c_str(),title.c_str(),1800,0.,1800.); //1800->2236
    	CHECK(histSvc->regHist(path.c_str(),WrongEvent[i]));
	*/


    name = "peakFinder_"+std::to_string(i);
    title = " Peak Finder "+std::to_string(i);
    path = "/file1/peakFinder/"+name;
    peakFinder[i] = new TH1F(name.c_str(),title.c_str(),10000,0.,10000.);
    CHECK(histSvc->regHist(path.c_str(),peakFinder[i]));

    name = "Saturation_"+std::to_string(i);
    title = "Saturation"+std::to_string(i);
    path = "/file1/saturation/"+name;
    saturation[i] = new TH1F(name.c_str(),title.c_str(),10000,0.,10000.);
    CHECK(histSvc->regHist(path.c_str(),saturation[i]));

	name = "PSE_"+std::to_string(i);
    title = "PSE_"+std::to_string(i);
    path = "/file1/PSE/"+name;
    PSE[i] = new TH1F(name.c_str(),title.c_str(),10000,0.,10000.);
    CHECK(histSvc->regHist(path.c_str(),PSE[i]));
	
    //calibration 2
    name = "calibration2_"+std::to_string(i);
    title = "C.Curve for each Trigger Tower "+std::to_string(i);
    path = "/file1/calibration2/"+name;
    calibration2[i] = new TH1F(name.c_str(),title.c_str(),10000,0.,10000.);
    CHECK(histSvc->regHist(path.c_str(),calibration2[i]));
	
	//calibration
    name = "calibration_"+std::to_string(i);
    title = "C.Curve for each Trigger Tower "+std::to_string(i);
    path = "/file1/calibration/"+name;
    calibration[i] = new TH1F(name.c_str(),title.c_str(),25,0.,2400.);
    CHECK(histSvc->regHist(path.c_str(),calibration[i]));
	
	//spectrum
	name = "spectrum_0"+std::to_string(i);
	title = "Spectrum_0 for each Trigger Tower "+std::to_string(i);
	//path = "/file1/spectrum_0/"+name;
	spectrum_0[i] = new TH1F(name.c_str(),title.c_str(),30000,0.,10000.);
	//CHECK(histSvc->regHist(path.c_str(),spectrum_0[i]));

	name = "spectrum_1"+std::to_string(i);
	title = "Spectrum_1 for each Trigger Tower "+std::to_string(i);
	//path = "/file1/spectrum_1/"+name;
	spectrum_1[i] = new TH1F(name.c_str(),title.c_str(),30000,0.,10000.);
	//CHECK(histSvc->regHist(path.c_str(),spectrum_1[i]));

	/*
	for (int w=0;w<15;w++){
	name = "tt"+std::to_string(i)+"adc_"+std::to_string(w);
	title = "ADC_"+std::to_string(w)+"for each Trigger Tower "+std::to_string(i);
	//path = "/file1/spectrum_1/"+name;
	ADChisto[i][w] = new TH2F(name.c_str(),title.c_str(),200,0.,10000.,100,0.,1240.);
	//CHECK(histSvc->regHist(path.c_str(),spectrum_1[i]));
	}
	*/

	/*
	//peak position versus adc number
	name = "peak vs adc_"+std::to_string(i);
	title = "Peak Position versus Adc Number";
	path = "/file1/peakpos/"+name;
	peak[i] = new TH1F(name.c_str(),title.c_str(),5,0.,5.);
	CHECK(histSvc->regHist(path.c_str(),peak[i]));
	*/

	//position versus adc value in the maximum
	name = "maximum vs maximum_"+std::to_string(i);
	title = "Maximum Adc Position versus Maximum Adc Value";
	path = "/file1/maxvsmax/"+name;
	mvsm[i] = new TH2F(name.c_str(),title.c_str(),1040,0.,1040,5,0.,5.);
	CHECK(histSvc->regHist(path.c_str(),mvsm[i]));
	
	
	name = "CorrETvsAdc_"+std::to_string(i);
	title = "Peak Adc Position versus ET";
	path = "/file1/corrADCvsET/"+name;
	corrETvsPeak[i] = new TH2F(name.c_str(),title.c_str(),800,0.,10000,100,0.,1040);
	CHECK(histSvc->regHist(path.c_str(),corrETvsPeak[i]));
	
  }
/*
   for(unsigned int l=0;l<number_TT;l++){	//2048->7168
	// 2-d histograms adc vs adcpeak
	//for each trigger tower
	for(unsigned int s=0;s<number_ADC;s++){
	
	//for the 5 adc slices
 	name = "adc_"+std::to_string(s);
 	title = "TH2F Histograms";
 	path = "/file1/TH2Fhisto/tt_"+std::to_string(l)+"/"+name;
    TH2Fhisto[l][s] = new TH2F(name.c_str(),title.c_str(),100,0.,1040.,100,0.,1040.);
    CHECK(histSvc->regHist(path.c_str(),TH2Fhisto[l][s]));
	
	name = "adc_"+std::to_string(s);
 	title = "TH2F cross check Histograms";
 	path = "/file1/crosscheck/tt_"+std::to_string(l)+"/"+name;
    	TH2Fcheck[l][s] = new TH2F(name.c_str(),title.c_str(),40,0.,1040.,40,0.,1040.);
    	CHECK(histSvc->regHist(path.c_str(),TH2Fcheck[l][s]));
	name = "adc_"+std::to_string(s);
 	title = "TH2F cross check2 Histograms";
 	path = "/file1/crosscheck2/tt_"+std::to_string(l)+"/"+name;
    	TH2Fcheck2[l][s] = new TH2F(name.c_str(),title.c_str(),40,0.,1040.,40,0.,1040.);
    	CHECK(histSvc->regHist(path.c_str(),TH2Fcheck2[l][s]));
 	 
	}


  }
  */
std::cout<<"one"<<std::endl;
for(unsigned int l=0;l<2;l++){	


    for (unsigned int t=0;t<15;t++){
	    name = "Step_"+std::to_string(t+1);
		title = "Step_"+std::to_string(t+1)+"Eta phi map of the PSE";
		path = "/file1/PSEmaps_"+std::to_string(l)+"/"+name;
		Step_PSE[t][l] =  new TH2TT(name.c_str(),title.c_str());
		CHECK(histSvc->regHist(path.c_str(),Step_PSE[t][l]));
	}
	 for (unsigned int t=0;t<15;t++){
	    name = "Step_"+std::to_string(t+1);
		title = "Step_"+std::to_string(t+1)+"Eta phi map of the distance of the Peak position from the first sat slice";
		path = "/file1/SatPeak_"+std::to_string(l)+"/"+name;
		SatPeak[t][l] =  new TH2TT(name.c_str(),title.c_str());
		CHECK(histSvc->regHist(path.c_str(),SatPeak[t][l]));
	}
	for (unsigned int t=0;t<15;t++){
		name = "Step_"+std::to_string(t+1);
 		title = "Step_"+std::to_string(t+1)+"Eta phi map of the ET";
 		path = "/file1/ETmaps_"+std::to_string(l)+"/"+name;
    	Step_ET[t][l] =  new TH2TT(name.c_str(),title.c_str());
    	CHECK(histSvc->regHist(path.c_str(),Step_ET[t][l]));
	}
	
	for (unsigned int t=0;t<15;t++){
		name = "Step_"+std::to_string(t+1);
	 	title = "Step_"+std::to_string(t+1)+"Eta phi map of the ADCs";
	 	path = "/file1/ADCmaps_"+std::to_string(l)+"/"+name;
	    Step_ADC[t][l] =  new TH2TT(name.c_str(),title.c_str());
	    CHECK(histSvc->regHist(path.c_str(),Step_ADC[t][l]));
	}

	for (unsigned int t=0;t<15;t++){
		name = "Step_"+std::to_string(t+1);
	 	title = "Step_"+std::to_string(t+1)+"Eta phi map of the NumSatADC";
	 	path = "/file1/SatADCmaps_"+std::to_string(l)+"/"+name;
	    Step_SatADC[t][l] =  new TH2TT(name.c_str(),title.c_str());
	    CHECK(histSvc->regHist(path.c_str(),Step_SatADC[t][l]));
	}
	for (unsigned int t=0;t<15;t++){
		name = "Step_"+std::to_string(t+1);
	 	title = "Step_"+std::to_string(t+1)+"Eta phi map of the Lut_jep";
	 	path = "/file1/Lut_jep_"+std::to_string(l)+"/"+name;
	    Step_Lut_jep[t][l] =  new TH2TT(name.c_str(),title.c_str());
	    CHECK(histSvc->regHist(path.c_str(),Step_Lut_jep[t][l]));
	}

	for (unsigned int s=0 ; s<3 ; s++){
		for (unsigned int t=0 ; t<15 ; t++){
	        name = "Step_"+std::to_string(t+1);
			title = "Step_"+std::to_string(t+1)+"Eta phi map of the RHL";
			path = "/file1/"+std::to_string(s)+"/RHL_"+std::to_string(l)+"/"+name;
			Step_RHL[t][l][s] =  new TH2TT(name.c_str(),title.c_str());
			CHECK(histSvc->regHist(path.c_str(),Step_RHL[t][l][s]));
        	}
	}
	
    for (unsigned int t=0;t<15;t++){
	    name = "Step_"+std::to_string(t+1);
		title = "Step_"+std::to_string(t+1)+"Eta phi map of the Adc(Peak - 1)";
		path = "/file1/BeforeP_"+std::to_string(l)+"/"+name;
		Step_BeforeP[t][l] =  new TH2TT(name.c_str(),title.c_str());
		CHECK(histSvc->regHist(path.c_str(),Step_BeforeP[t][l]));
        }
	for (unsigned int t=0;t<15;t++){
	    name = "Step_"+std::to_string(t+1);
		title = "Step_"+std::to_string(t+1)+" Step Check";
		path = "/file1/Check_"+std::to_string(l)+"/"+name;
		Step_Check[t][l] =  new TH2TT(name.c_str(),title.c_str());
		CHECK(histSvc->regHist(path.c_str(),Step_Check[t][l]));
        }
	for (unsigned int t=0;t<15;t++){
        name = "Step_event_"+std::to_string(t+1);
		title = "Step_event_"+std::to_string(t+1);
		path = "/file1/event_"+std::to_string(l)+"/"+name;
		Step_event[t][l] =  new TH2TT(name.c_str(),title.c_str());
		CHECK(histSvc->regHist(path.c_str(),Step_event[t][l]));
        }
	for (unsigned int t=0;t<15;t++){
        name = "Step_secondET_"+std::to_string(t+1);
		title = "Step_secondET_"+std::to_string(t+1);
		path = "/file1/secondET_"+std::to_string(l)+"/"+name;
		Step_secondET[t][l] =  new TH2TT(name.c_str(),title.c_str());
		CHECK(histSvc->regHist(path.c_str(),Step_secondET[t][l]));
        }
	for (unsigned int t=0;t<15;t++){
        name = "Step_secondSatADC_"+std::to_string(t+1);
		title = "Step_secondSatADC_"+std::to_string(t+1);
		path = "/file1/secondSatADC_"+std::to_string(l)+"/"+name;
		Step_secondSatADC[t][l] =  new TH2TT(name.c_str(),title.c_str());
		CHECK(histSvc->regHist(path.c_str(),Step_secondSatADC[t][l]));
        }
    for (unsigned int t=0;t<15;t++){
        name = "Step_"+std::to_string(t+1);
		title = "result_"+std::to_string(t+1);
		path = "/file1/result_"+std::to_string(l)+"/"+name;
		result[t][l] =  new TH2TT(name.c_str(),title.c_str());
		CHECK(histSvc->regHist(path.c_str(),result[t][l]));
        }
    for (unsigned int t=0;t<15;t++){
        name = "fail_"+std::to_string(t+1);
		title = "fail_"+std::to_string(t+1);
		path = "/file1/fail_"+std::to_string(l)+"/"+name;
		fail[t][l] =  new TH2TT(name.c_str(),title.c_str());
		CHECK(histSvc->regHist(path.c_str(),fail[t][l]));
        }
    for (unsigned int t=0;t<15;t++){
        name = "Step_"+std::to_string(t+1);
		title = "Step_"+std::to_string(t+1);
		path = "/file1/logic_"+std::to_string(l)+"/"+name;
		logic[t][l] =  new TH2TT(name.c_str(),title.c_str());
		CHECK(histSvc->regHist(path.c_str(),logic[t][l]));
        }
    for (unsigned int t=0;t<15;t++){
        name = "Step_"+std::to_string(t+1);
		title = "Step_"+std::to_string(t+1);
		path = "/file1/logic_wrong"+std::to_string(l)+"/"+name;
		logic_wrong[t][l] =  new TH2TT(name.c_str(),title.c_str());
		CHECK(histSvc->regHist(path.c_str(),logic_wrong[t][l]));
        }

}

    name = "Step";
	title = "S+1 - (s-1.5)-t_low  &&  (s-0.5)-t_high";
	path = "/file1/S+1/"+name;
	S_1 =  new TH2F(name.c_str(),title.c_str(),200,0,20000,300,-1000,1000);
	CHECK(histSvc->regHist(path.c_str(),S_1));

    name = "Step";
	title = "S - (s-1.5)-t_low";
	path = "/file1/S/"+name;
	S =  new TH2F(name.c_str(),title.c_str(),200,0,20000,300,-1000,1000);
	CHECK(histSvc->regHist(path.c_str(),S));

    name = "Step";
	title = "S+2 - (s-0.5)-t_high";
	path = "/file1/S+2/"+name;
	S_2 =  new TH2F(name.c_str(),title.c_str(),200,0,20000,300,-1000,1000);
	CHECK(histSvc->regHist(path.c_str(),S_2));

	name = "Step";
	title = "S+1 - (s-1.5)-t_low  &&  (s-0.5)-t_high";
	path = "/file1/S+1_wrong1/"+name;
	S_1_wrong =  new TH2F(name.c_str(),title.c_str(),200,0,20000,300,-1000,1000);
	CHECK(histSvc->regHist(path.c_str(),S_1_wrong));

    name = "Step";
	title = "S - (s-1.5)-t_low";
	path = "/file1/S_wrong1/"+name;
	S_wrong =  new TH2F(name.c_str(),title.c_str(),200,0,20000,300,-1000,1000);
	CHECK(histSvc->regHist(path.c_str(),S_wrong));

    name = "Step";
	title = "S+2 - (s-0.5)-t_high";
	path = "/file1/S+2_wrong1/"+name;
	S_2_wrong =  new TH2F(name.c_str(),title.c_str(),200,0,20000,300,-1000,1000);
	CHECK(histSvc->regHist(path.c_str(),S_2_wrong));

	name = "Step";
	title = "h_l_wrong";
	path = "/file1/h_l_wrong/"+name;
	h_l_wrong =  new TH2F(name.c_str(),title.c_str(),200,0,20000,300,-1000,1000);
	CHECK(histSvc->regHist(path.c_str(),h_l_wrong));

    name = "Step";
	title = "l_wrong";
	path = "/file1/l_wrong/"+name;
	l_wrong =  new TH2F(name.c_str(),title.c_str(),200,0,20000,300,-1000,1000);
	CHECK(histSvc->regHist(path.c_str(),l_wrong));

    name = "Step";
	title = "h_wrong";
	path = "/file1/h_wrong/"+name;
	h_wrong =  new TH2F(name.c_str(),title.c_str(),200,0,20000,300,-1000,1000);
	CHECK(histSvc->regHist(path.c_str(),h_wrong));

	/*
	for(int s=0;s<15;s++){
		name = "tt 0x011d0f03 ADC_"+std::to_string(s);
 		title = "TH2F Histograms ADC_"+std::to_string(s);
 		path = "/file1/TH2Fhisto/"+name;
    	TH2Fhisto[s] = new TH2F(name.c_str(),title.c_str(),300,0.,10000.,100,0.,1040.);
    	CHECK(histSvc->regHist(path.c_str(),TH2Fhisto[s]));
    }
	*/
	
    for(int t=0; t<66; t++){
    	for(int s=0;s<15;s++){
			name = "etaADC_"+std::to_string(s)+"eta_"+std::to_string(t);
 			title = "TH2F Histograms ADC_"+std::to_string(s);
 			//path = "/file1/TH2Feta/"+name;
    		TH2Feta[t][s] = new TH2F(name.c_str(),title.c_str(),200,0.,10000.,100,0.,1240.);
    		//CHECK(histSvc->regHist(path.c_str(),TH2Feta[t][s]));
    	}
	}

/*

for (unsigned int t=0;t<number_TT;t++){
	for (unsigned int l=0 ; l < 30 ; l++ ){
        	name = "Calc"+std::to_string(t+1);
		title = "Calc"+std::to_string(t+1);
		path = "/file1/Calc_"+std::to_string(l)+"/"+name;
		Calc[t][l] =  new TH1D(name.c_str(),title.c_str(),20000,0,20000.);
		CHECK(histSvc->regHist(path.c_str(),Calc[t][l]));
       }
}

*/


//=========================================MAP=======================================

std::ifstream f1("PprSatBcidResults_Physics.pulsers.revisedSat80.coolinit.txt");
std::string coolId;
std::string line;
std::string low_t;
std::string high_t; 


int dim = 0 ;
int cont=0;

while ( f1.good() ){
	getline( f1 , line );
	cont = 0;
	dim=0;
	coolId="";
	high_t="";
	low_t="";

for( std::string::iterator it = line.begin(); it!=line.end() ; it++){
      dim ++;
    }
for (int i=1; i<dim-1; i++){   
    int t=0;   
      	if (line[i]==',' && line[i-1]=='s'){ //b,
			for (int t=0;t<10;t++){
	  			coolId+=line[i+1+t] ;
			}	 
      	}
      	t=0;
      	if (line[i]==':' && line[i-1]=='t' && cont ==1 && i>=130){
			while (line[i+1+t]!=','){
	  			high_t+=line[i+1+t] ;
	  			t++;
			}
			cont++;
      	}
      	t=0;
    	if (line[i]==':' && line[i-1]=='t' && cont==0 && i>=130){
			while (line[i+1+t]!=','){
	  			low_t+=line[i+1+t] ;
				t++;
			} 
		cont=1;
      	}
    }

int i_low_t =std::atoi(low_t.c_str());
//std::cout<<i_low_t<<std::endl;
int i_high_t =std::atoi(high_t.c_str());
//std::cout<<i_high_t<<std::endl;
//int i_coolId = std::atoi(coolId.c_str());
//coolId = std::to_string(i_coolId);
//std::cout<<coolId<<std::endl;

m_high_t.insert ( std::make_pair(coolId,i_high_t));
m_low_t.insert ( std::make_pair(coolId,i_low_t));  
}
std::cout<<""<<std::endl;

//===================================================================================
  return StatusCode::SUCCESS;
}

StatusCode MyAlg::finalize() {
/*
  ServiceHandle<ITHistSvc> histSvc("THistSvc",name());
  CHECK( histSvc.retrieve() );


std::string name, title;
std::string name1, title1;
std::string name2, title2;
 
 for (int p=0;p<3;p++){
  name = "lE_P_Map_"+std::to_string(p);
  title = " lE_P_Map_"+std::to_string(p);
  
  name1 = "lE_P_Map_NB_"+std::to_string(p);
  title1 = " lE_P_Map_NB_"+std::to_string(p);
  
  name2 = "lE_P_Map_NB_NS_"+std::to_string(p);
  title2 = "lE_P_Map_NB_NS_"+std::to_string(p);
  
  lE_P_Map[p]= new TH2TT(name.c_str(),title.c_str());
  lE_P_Map_NB[p]= new TH2TT(name1.c_str(),title1.c_str());
  lE_P_Map_NB_NS[p]= new TH2TT(name2.c_str(),title2.c_str());
 } 

for (int i=0;i<number_TT;i++){	//2048->7168
	m_average[i] = int(m_average[i]*10/2235);	//1799->2235
   	m_average1[i] = int(m_average1[i]*10/2235);
   	m_average2[i] = int(m_average2[i]*10/m_divide[i]);
   	for (int j=0;j<m_average[i];j++){
   	  lE_P_Map[m_layer[i]]->Fill(m_eta[i],m_phi[i]);
   	}
   	for (int k=0;k<m_average1[i];k++){
    	 lE_P_Map_NB[m_layer[i]]->Fill(m_eta[i],m_phi[i]);
   	}
   	for (int l=0;l<m_average2[i];l++){
    	 lE_P_Map_NB_NS[m_layer[i]]->Fill(m_eta[i],m_phi[i]);
   	}
 }
 TFile *f = new TFile("maps_294600_LAR.root","RECREATE");
 for(int p=0;p<3;p++){
   lE_P_Map[p]->Write();
   lE_P_Map[p]->Delete();
   
   lE_P_Map_NB[p]->Write();
   lE_P_Map_NB[p]->Delete();
   
   lE_P_Map_NB_NS[p]->Write();
   lE_P_Map_NB_NS[p]->Delete();
 }
 f->Close();

int y=0;
FILE *brokentt;
brokentt = fopen("brokentt_294593_LAR.txt","w");
for (int i=0;i<number_TT;i++){
	
	m_sum[i] = m_sum[i]/m_count1[i];
	m_bcid[i] = m_sumBCID[i]/m_count1[i];

	for (int j=0;j<m_sum[i];j ++) {
		calibration[i]->Fill(m_count2[i]);
		calibration2[i]->Fill(caloET[i]);
	}
	
	for (int j=0; j< m_bcid[i]; j++){
		PSE[i]->Fill(caloET[i]);
	}	
	if(m_broken[i]==0){
	        y++;
	        fprintf(brokentt,"%d",i);
		std::cout<<y<<") "<<i<<std::endl;
	} 
	

 }
fclose(brokentt);
*/
  return StatusCode::SUCCESS;

}

 StatusCode MyAlg::execute() {  
 ATH_MSG_DEBUG ("Executing " << name() << "...");


 const xAOD::EventInfo* eventInfo = 0;  //initialize a pointer 
 CHECK( evtStore()->retrieve(eventInfo)); // pointer to event storegate


 const DataVector<xAOD::TriggerTower>* trigTowColl = 0; //initialize a pointer "trigTowColl" that points at the method TriggerTower(that produces a vector)
 CHECK( evtStore()->retrieve(trigTowColl,"xAODTriggerTowers")); //pointer to the container xAODTriggerTowers

 
 ServiceHandle<ITHistSvc> histSvc("THistSvc",name());
 CHECK( histSvc.retrieve() );


// pulse shape of one trigger tower 
for(unsigned int j=0;j<(trigTowColl->at(0)->adc()).size();j++){
	//I'm filling the histogram bin to bin (17 bins) with the number of the correspondig adc, leaving empthy the two border bins (0 and 17)	
	for (unsigned int l=0;l<(trigTowColl->at(0)->adc()).at(j);l++){		
		pulseShape[eventInfo->eventNumber()]->Fill(j);
		}	
	}



int n_tt = trigTowColl->size();	
/*
if ((eventInfo->eventNumber())>0){
	//find broken trigger towers	
	for (int i=0;i<n_tt;i++){
		if ( (trigTowColl->at(i)->adc()).at(3)>100){
			m_broken[i] = 1;
			}			
		}	
	}
*/		
int h=0;
int l=0;
for (int i=0;i<n_tt;i++){
//std::cout<<trigTowColl->at(i)->adc().size()<<std::endl;
	/*
	for (unsigned int t=0 ; t < number_ADC ; t++ ){
		pulse[t] = trigTowColl->at(i)->adc().at(2*t+1);
		if(i==136){
			for ( unsigned int n = 0 ; n < pulse[t] ; n++ ){
				pulseShape[eventInfo->eventNumber()]->Fill(t);
			}
		}
	}
	*/
if (m_broken[i]==1){
	auto x = trigTowColl->at(i)->auxdataConst<std::vector<float>>("CaloCellEnergyByLayer");
	float sum=0;
	for (unsigned int j=0; j<x.size(); j++){
		sum=x.at(j) +sum;
	}
		
	caloET[i]= sum;	
	m_max[i]=0;
	m_maxpos[i]=0;
	m_sat[i]=0;
	m_sat_odd[i]=0;

	if(eventInfo->eventNumber()==0){
		h=0;
		for (int d=0;d<66;d++){
			if (etaslice[d]!=trigTowColl->at(i)->eta()){
				h++;
			}
			if(h==66){
				etaslice[l]=trigTowColl->at(i)->eta();
				std::cout<<etaslice[l]<<" "<<h<<" "<<l<<std::endl;
				l++;	
			}
		}
	}

	// for one trigger tower, first I discart the first event that is strange respect of the others
	if((eventInfo->eventNumber())>0 ){
			//I select the value of the central adc for the first event as the test value	
			// find the maximum of the pulseshape that is not always in the central bin
			//for (unsigned int j = 0; j < (trigTowColl->at(i)->adc()).size(); j++){
			/*
			for (unsigned int j= 0 ; j < number_ADC ; j ++){
				//if ((trigTowColl->at(i)->adc()).at(j) >= m_max[i]){
 				//m_max[i] = (trigTowColl->at(i)->adc()).at(j);
					
				if (pulse[j] >= m_max[i]){
					m_max[i] = pulse[j] ;
					if (j>0){
					  	//m_max_prime[i] = (trigTowColl->at(i)->adc()).at(j-1);	
					  	m_max_prime[i] = pulse[j-1];
					}
					else{
					    m_max_prime[i] = 0;
					}
					  m_maxpos[i] = j;
				}	
				//if ((trigTowColl->at(i)->adc()).at(j)>1020){
				if ( pulse[j]>1020){
						m_sat[i]++;
						if (m_sat[i] == 1){
							m_distance[i] = j;
						}
				}
				
			}
			*/
	  
		
		for (unsigned int j= 0 ; j < trigTowColl->at(i)->adc().size() ; j ++){
			if ((trigTowColl->at(i)->adc()).at(j) >= m_max[i]){
 				m_max[i] = (trigTowColl->at(i)->adc()).at(j);
				if (j>0){
					m_max_prime[i] = (trigTowColl->at(i)->adc()).at(j-1);	
				  	//m_max_prime[i] = pulse[j-1];
				}
				else{
				    m_max_prime[i] = 0;
				}
					  m_maxpos[i] = j;
				}	
				if ((trigTowColl->at(i)->adc()).at(j)>1022){
				//if ( pulse[j]>1020){
				
						m_sat[i]++;
						if(j%2 != 0){
							m_sat_odd[i]++;
							if (m_sat_odd[i] == 1){
								m_distance_odd[i] = j;
							}
						}
						if (m_sat[i] == 1){
							m_distance[i] = j;
						}

						
				}
					//std::cout<<m_distance_odd[i]<<std::endl;
			}
		
		/*
		if (m_maxpos[i]<1 && m_sat[i]<2){
				WrongEvent[i]->Fill(eventInfo->eventNumber());
				if(m_broken[i]==1){
					TotalWrongEvent->Fill(eventInfo->eventNumber());
					}		
			}
		*/
			m_bcid[i] = trigTowColl->at(i)->bcidVec().at(0);
        	m_bcid[i] &= 0x6; 
        	//std::cout<<"ADC="<<trigTowColl->at(i)->adc().size()<<std::endl;
			m_lut_jep[i] = int(trigTowColl->at(i)->lut_jep().at(0));
			auto bits = trigTowColl->at(i)->sat80Vec().at(0);
			m_rhl0[i]= int(bits & 0x1);
			bits = trigTowColl->at(i)->sat80Vec().at(0);
			m_rhl1[i] = int(bits & 0x2);
			bits = trigTowColl->at(i)->sat80Vec().at(0);
			m_rhl2[i] = int(bits &= 0x4);
			
			



     			
			//I give it an interval of acceptance ( smaller than the 11 percent)		
			//if (caloET[i]<m_caloET_test[i]+m_caloET_test[i]*0.11){
			m_lay=trigTowColl->at(i)->layer();

			if(m_lut_jep[i]==0){
				failing[i]++;
			}



				
			std::stringstream s1;
			if(i>=0 && i<=1023){
			s1<<"0x00"<<std::hex<<trigTowColl->at(i)->coolId();
			}
			else{
			s1<<"0x0"<<std::hex<<trigTowColl->at(i)->coolId();
			}
			std::string r1(s1.str());
			int v_low_t,v_high_t;
			v_low_t = m_low_t[r1];
			v_high_t = m_high_t[r1];
			int branch;
			branch=0;

			if(m_distance_odd[i]-2>=0){			
				if (trigTowColl->at(i)->adc().at(m_distance_odd[i]-2)>v_high_t) {
					if(m_distance_odd[i]-3>=0){	
						if(trigTowColl->at(i)->adc().at(m_distance_odd[i]-3)>v_low_t){
							if(i==1919){
								std::cout<<"pippo"<<caloET[i]<<" "<<trigTowColl->at(i)->adc().at(m_distance_odd[i]-3)-v_high_t<<std::endl;
								S->Fill(caloET[i],trigTowColl->at(i)->adc().at(m_distance_odd[i]-3)-v_low_t);
								branch=1;
							}
						}
				
						else {
							if(i==1919){
								std::cout<<"pippo"<<caloET[i]<<" "<<trigTowColl->at(i)->adc().at(m_distance_odd[i]-3)-v_high_t<<std::endl;
								S_1->Fill(caloET[i],trigTowColl->at(i)->adc().at(m_distance_odd[i]-3)-v_low_t);
								branch=2;
							}
						}
					}
				}			
					else{
				
						if(trigTowColl->at(i)->adc().at(m_distance_odd[i]-1)<=v_high_t){
							if(i==1919){
								std::cout<<"pippo"<<caloET[i]<<" "<<trigTowColl->at(i)->adc().at(m_distance_odd[i]-1)-v_high_t<<std::endl;
								S_2->Fill(caloET[i],trigTowColl->at(i)->adc().at(m_distance_odd[i]-1)-v_high_t);
								branch=4;
							}
						}
				
						else {
							if(i==1919){
								std::cout<<"pippo"<<caloET[i]<<" "<<trigTowColl->at(i)->adc().at(m_distance_odd[i]-1)-v_high_t<<std::endl;
								S_1->Fill(caloET[i],trigTowColl->at(i)->adc().at(m_distance_odd[i]-1)-v_high_t);
								branch=3;
								}						
						}
					}						
			}

			if (i==1919){
				if (m_distance_odd[i]==7 && branch!=1 ){
					S_wrong->Fill(caloET[i],trigTowColl->at(i)->adc().at(m_distance_odd[i]-3)-v_low_t);
				}
				if (m_distance_odd[i]==5 && branch!=2 ){
					S_1_wrong->Fill(caloET[i],trigTowColl->at(i)->adc().at(m_distance_odd[i]-3)-v_low_t);
				}
				if (m_distance_odd[i]==5 && branch!=3 ){
					S_1_wrong->Fill(caloET[i],trigTowColl->at(i)->adc().at(m_distance_odd[i]-1)-v_high_t);
				}
				if (m_distance_odd[i]==3 && branch!=4 ){
					S_2_wrong->Fill(caloET[i],trigTowColl->at(i)->adc().at(m_distance_odd[i]-1)-v_high_t);
				}
				/*
				for(int num = 0 ; num < 15 ; num++){
					TH2Fhisto[num]->Fill(caloET[1919],trigTowColl->at(1919)->adc().at(num));
				}
				*/

			}
			/*
			for(int w=0;w<15;w++){
				ADChisto[i][w]->Fill(caloET[i],trigTowColl->at(i)->adc().at(w));
			}
			*/
			if(m_lay==0){
				for(int w=0;w<15;w++){
					for(int s=0;s<66;s++){
						if(trigTowColl->at(i)->eta()==etaslice[s]){
							TH2Feta[s][w]->Fill(caloET[i],trigTowColl->at(i)->adc().at(w));
						}
					}
				}
			}

			if (i==1919){
				//if (m_distance_odd[i]==7 && branch!=1 ){
				//	S_wrong->Fill(caloET[i],trigTowColl->at(i)->adc().at(m_distance_odd[i]-3)-v_low_t);
				//}
				if (m_distance_odd[i]==5 && branch!=2 && branch!=3 ){
					if (trigTowColl->at(i)->adc().at(m_distance_odd[i]-2)<v_high_t && trigTowColl->at(i)->adc().at(m_distance_odd[i]-3)<v_low_t){
						h_wrong->Fill(caloET[i],trigTowColl->at(i)->adc().at(m_distance_odd[i]-3)-v_high_t);
					}
					if (trigTowColl->at(i)->adc().at(m_distance_odd[i]-2)>v_high_t && trigTowColl->at(i)->adc().at(m_distance_odd[i]-3)>v_low_t){
						l_wrong->Fill(caloET[i],trigTowColl->at(i)->adc().at(m_distance_odd[i]-3)-v_low_t);
					}
					if (trigTowColl->at(i)->adc().at(m_distance_odd[i]-2)<v_high_t && trigTowColl->at(i)->adc().at(m_distance_odd[i]-3)>v_low_t){
						h_l_wrong->Fill(caloET[i],trigTowColl->at(i)->adc().at(m_distance_odd[i]-3)-v_low_t);
					}
				}
				//if (m_distance_odd[i]==5 && branch!=3 ){
				//	S_1_wrong->Fill(caloET[i],trigTowColl->at(i)->adc().at(m_distance_odd[i]-1)-v_high_t);
				//}
				//if (m_distance_odd[i]==3 && branch!=4 ){
				//	S_2_wrong->Fill(caloET[i],trigTowColl->at(i)->adc().at(m_distance_odd[i]-1)-v_high_t);
				//}
			}




			if(eventInfo->eventNumber()%200 != 0 || eventInfo->eventNumber()==1 ){
				//the counter count how many events respect the conditione imposed			
				m_count1[i] ++ ;
				//this is a sum of all the adc values 
				m_sum[i] = m_sum[i] + m_max[i];
				m_sumBCID[i] = m_sumBCID[i] + m_bcid[i];
				//new part!!
				m_lay=trigTowColl->at(i)->layer();
				/*
				(*events_step[i][m_step[i]+m_lay*15])++;
				Calc[i][m_step[i]+m_lay*15]->Fill(caloET[i]);
				*/
				
			}
   			
		// when we have a value that is out of the intervall
			else {
				//we do the averege
				m_sum[i] = m_sum[i]/m_count1[i];
				m_sumBCID[i] = m_sumBCID[i]/m_count1[i];
				// we fill the considered bin with the average
				for (int j=0;j<m_sum[i];j++){
					calibration[i]->Fill(m_count2[i]);
					calibration2[i]->Fill(caloET[i]);
					}
				for (int j=0; j< m_sumBCID[i]; j++){
					PSE[i]->Fill(caloET[i]);
				}				
				/*
				if (int(trigTowColl->at(i)->coolId())==118950913){
					std::cout<<trigTowColl->at(i)->phi()<<" "<<trigTowColl->at(i)->eta()<<std::endl;
					std::cout<<"tt "<<std::to_string(trigTowColl->at(i)->coolId())<<"at step "<<m_step[i]<<std::endl;
					std::cout<<"adc counts = "<<m_max[i]<<std::endl;
					std::cout<<"number of satslices = "<<m_sat[i]<<std::endl;
					std::cout<<"recontructed Et = "<<caloET[i]<<std::endl;
					std::cout<<"recontructed lut_jep = "<<m_lut_jep[i]<<std::endl;
				}
				*/
				//fill eta phi maps
				m_lay=trigTowColl->at(i)->layer();
				Step_Check[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());

				for (int k=0;k<int(caloET[i]);k++){
					Step_ET[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
				}
				for (int k=0;k<int(m_max[i]);k++){
					Step_ADC[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
				}
				for (int k=0;k<int(m_bcid[i]);k++){
				        Step_PSE[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
				}
				for (int k=0;k<int(3-m_distance[i]);k++){
				        SatPeak[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
				}
				for (int k=0;k<int(m_sat[i]);k++){
				        Step_SatADC[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
				}
				for (int k=0;k<int(m_lut_jep[i]);k++){
				        Step_Lut_jep[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
				}
				for (int k=0;k<int(m_max_prime[i]);k++){
				        Step_BeforeP[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
				}
				for (int k=0;k<int(eventInfo->eventNumber());k++){
				  Step_event[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
				}       
				for (int k=0;k<int(m_rhl0[i]);k++){
				     	Step_RHL[m_step[i]][m_lay][0]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
				}	
				for (int k=0;k<int(m_rhl1[i]);k++){
				     	Step_RHL[m_step[i]][m_lay][1]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
				} 
				for (int k=0;k<int(m_rhl2[i]);k++){
			    	 	Step_RHL[m_step[i]][m_lay][2]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
				}
				if (int(m_lut_jep[i])==0){
					for (int k=0;k<int(m_sat[i]);k++){
				       		Step_secondSatADC[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
					}
					for (int k=0;k<int(caloET[i]);k++){
					     	Step_secondET[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
					}
				}
				for (int n=0 ; n < failing[i] ; n++ ){
					fail[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
				}

				//====================================DECISION LOGIC======================================	
				
				std::stringstream s1;
				if(i>=0 && i<=1023){
				s1<<"0x00"<<std::hex<<trigTowColl->at(i)->coolId();
				}
				else{
				s1<<"0x0"<<std::hex<<trigTowColl->at(i)->coolId();
				}
				std::string r1(s1.str());
				int v_low_t,v_high_t;
				v_low_t = m_low_t[r1];
				v_high_t = m_high_t[r1];
				std::cout<<i<< " tt=" <<r1<< "v_low_t=" << v_low_t << "v_high_t=" << v_high_t <<std::endl;
				//std::cout<<m_distance_odd[i]<<std::endl;
				if(m_distance_odd[i]-2>=0){			

					if (trigTowColl->at(i)->adc().at(m_distance_odd[i]-2)>v_high_t) {
						if(m_distance_odd[i]-3>=0){	
							if(trigTowColl->at(i)->adc().at(m_distance_odd[i]-3)>v_low_t){

								if(m_distance_odd[i]==central){
									for (int t = 0 ; t < 4 ; t++ ){
										result[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
										logic[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
									}
								}
								else{
									std::cout<<i<<"exp="<<central<<" data="<<m_distance_odd[i]<<" branch="<<"1 "<<trigTowColl->at(i)->adc().at(m_distance_odd[i]-2)<<" > "<<v_high_t<<" "<<trigTowColl->at(i)->adc().at(m_distance_odd[i]-3)<<">"<<v_low_t<<std::endl;
								}
							}
					
							else {

								if(m_distance_odd[i]+2==central){
									for (int t = 0 ; t < 4 ; t++ ){
										result[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
									}
									for(int t=0 ; t<2 ; t++){
										logic[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
									}
								}

								else{
									std::cout<<i<<"exp="<<central-2<<" data="<<m_distance_odd[i]<<" branch="<<"2 "<<trigTowColl->at(i)->adc().at(m_distance_odd[i]-2)<<" > "<<v_high_t<<" "<<trigTowColl->at(i)->adc().at(m_distance_odd[i]-3)<<"<="<<v_low_t<<std::endl;
								}
							}
						}
					}			
					

					else{
					
							if(trigTowColl->at(i)->adc().at(m_distance_odd[i]-1)<=v_high_t){

								if(m_distance_odd[i]+4==central){
									for (int t = 0 ; t < 4 ; t++ ){
										result[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
									}
									for(int t=0 ; t<3 ; t++){
										logic[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
									}
								}
								else{
									std::cout<<i<<"exp="<<central-4<<" data="<<m_distance_odd[i]<<" branch="<<"3 "<<trigTowColl->at(i)->adc().at(m_distance_odd[i]-2)<<" <= "<<v_high_t<<" "<<trigTowColl->at(i)->adc().at(m_distance_odd[i]-1)<<"<="<<v_high_t<<std::endl;
								}

							}
					
							else {

								if(m_distance_odd[i]+2==central){
									for (int t = 0 ; t < 4 ; t++ ){
										result[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
									}
									for(int t=0 ; t<2 ; t++){
										logic[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
									}
								}
								else{
									std::cout<<i<<"exp="<<central-2<<" data="<<m_distance_odd[i]<<" branch="<<"4 "<<trigTowColl->at(i)->adc().at(m_distance_odd[i]-2)<<" <= "<<v_high_t<<" "<<trigTowColl->at(i)->adc().at(m_distance_odd[i]-1)<<">"<<v_high_t<<std::endl;
								}						
							}
						}					
					
				}
				if (m_distance_odd[i]==7 && branch!=1 ){
					logic_wrong[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
				}
				if (m_distance_odd[i]==5 && branch!=2 ){
					for(unsigned int g=0;g<2;g++){
						logic_wrong[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
					}
				}
				if (m_distance_odd[i]==5 && branch!=3 ){
					for(unsigned int g=0;g<2;g++){
						logic_wrong[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
					}
				}
				if (m_distance_odd[i]==3 && branch!=4 ){
					for(unsigned int g=0;g<3;g++){
						logic_wrong[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
					}
				}
		//========================================================================================

				m_step[i]++;
				//we set the new values for adc_test and for sum
				m_sum[i] = m_max[i];
        	    m_adc_test[i] = m_sum[i];
            	m_caloET_test[i] = caloET[i];
            	m_sumBCID[i] = m_bcid[i];
           	 	m_count1[i]=1;
           	 	failing[i]=0;
            	m_count2[i]=eventInfo->eventNumber();
			}

		m_lay=trigTowColl->at(i)->layer();

		if (m_lay==0){
			spectrum_0[i]->Fill(caloET[i]);
		}
		if (m_lay==1){
			spectrum_1[i]->Fill(caloET[i]);
		}
		if (m_lay==2){
			for (int h=0;h<1000;h++){
				std::cout<<"abort"<<std::endl;
			}
		}
		if (m_maxpos[i]>1){
		    //std::cout<<i<<std::endl;
			corrETvsPeak[i]->Fill(caloET[i],m_max[i]);
			}
		//filling the 2-d histograms
		//for (unsigned int j = 0; j < (trigTowColl->at(i)->adc()).size(); j++){
		//	if(m_sat[i]<2){

		//		TH2Fhisto[i][j]->Fill(m_max[i],(trigTowColl->at(i)->adc()).at(j));
				
		//		}
		//	if (m_maxpos[i]==7){
		
		//		TH2Fcheck[i][j]->Fill(m_max[i],(trigTowColl->at(i)->adc()).at(j));

		//		}
    	//	}
	      		
		//this part of the code is to shift all the pulseshape
			
			
		int bcid = trigTowColl->at(i)->bcidVec().at(0);
		bcid &= 0x6;
			
		if(bcid==4 || bcid==6) {
			peakFinder[i]->SetBinContent(int(caloET[i]),10);
		}
 		else if(bcid==2 || bcid==6){
			saturation[i]->SetBinContent(int(caloET[i]),10);			
			}		
		m_average[i] = m_average[i] + m_maxpos[i];
		
		if(m_broken[i]==1){
			m_average1[i] = m_average1[i] + m_maxpos[i];

			if (m_sat[i]<2 ){	
				m_average2[i] = m_average2[i] + m_maxpos[i];
				m_divide[i]=eventInfo->eventNumber();
				}
		}
		


			//set the right name of the trigger tower
			if (eventInfo->eventNumber()==events-1){
			  
				m_lay=trigTowColl->at(i)->layer();
			    for (int k=0;k<int(caloET[i]);k++){
				     Step_ET[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
				}
				for (int k=0;k<int(m_max[i]);k++){
				     Step_ADC[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
				}
				for (int k=0;k<int(3-m_distance[i]);k++){
				     SatPeak[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
				}
				for (int k=0;k<int(m_bcid[i]);k++){
				     Step_PSE[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
				}
				for (int k=0;k<int(m_sat[i]);k++){
				     Step_SatADC[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
				}
				for (int k=0;k<int(m_lut_jep[i]);k++){
				      Step_Lut_jep[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
				}

				for (int k=0;k<int(m_rhl0[i]);k++){
				     	Step_RHL[m_step[i]][m_lay][0]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
                                }
				
				for (int k=0;k<int(m_rhl1[i]);k++){
				     	Step_RHL[m_step[i]][m_lay][1]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
                                }
				
				for (int k=0;k<int(m_rhl2[i]);k++){
				     	Step_RHL[m_step[i]][m_lay][2]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
                                }


				for (int k=0;k<int(m_max_prime[i]);k++){
				      Step_BeforeP[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
				}
				if (m_lay==0){
					for (int k = 0 ; k < m_step[i] ; k ++){
					numberStep_0->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
					}
				}
				if (m_lay==1){
					for (int k = 0 ; k < m_step[i] ; k ++){
					numberStep_1->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
					}
				}
				for (int k=0;k<int(eventInfo->eventNumber());k++){
				     	Step_event[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
                                }

				if (int(m_lut_jep[i])==0){
					for (int k=0;k<int(m_sat[i]);k++){
				       		Step_secondSatADC[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
					}
					for (int k=0;k<int(caloET[i]);k++){
				       		Step_secondET[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
					}
				}
				for (int n=0 ; n < failing[i] ; n++ ){
					fail[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
				}

				std::stringstream s1;
				if(i>=0 && i<=1023){
				s1<<"0x00"<<std::hex<<trigTowColl->at(i)->coolId();
				}
				else{
				s1<<"0x0"<<std::hex<<trigTowColl->at(i)->coolId();
				}
				std::string r1(s1.str());
				int v_low_t,v_high_t;
				v_low_t = m_low_t[r1];
				v_high_t = m_high_t[r1];
				std::cout<<i<< " tt=" <<r1<< "v_low_t=" << v_low_t << "v_high_t=" << v_high_t <<std::endl;
				//std::cout<<m_distance_odd[i]<<std::endl;
				if(m_distance_odd[i]-2>=0){			

					if (trigTowColl->at(i)->adc().at(m_distance_odd[i]-2)>v_high_t) {
						if(m_distance_odd[i]-3>=0){	
							if(trigTowColl->at(i)->adc().at(m_distance_odd[i]-3)>v_low_t){

								if(m_distance_odd[i]==central){
									for (int t = 0 ; t < 4 ; t++ ){
										result[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
										logic[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
									}
								}
								else{
									std::cout<<i<<"exp="<<central<<" data="<<m_distance_odd[i]<<" branch="<<"1 "<<trigTowColl->at(i)->adc().at(m_distance_odd[i]-2)<<" > "<<v_high_t<<" "<<trigTowColl->at(i)->adc().at(m_distance_odd[i]-3)<<">"<<v_low_t<<std::endl;
								}
							}
					
							else {

								if(m_distance_odd[i]+2==central){
									for (int t = 0 ; t < 4 ; t++ ){
										result[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
									}
									for(int t=0 ; t<2 ; t++){
										logic[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
									}
								}

								else{
									std::cout<<i<<"exp="<<central-2<<" data="<<m_distance_odd[i]<<" branch="<<"2 "<<trigTowColl->at(i)->adc().at(m_distance_odd[i]-2)<<" > "<<v_high_t<<" "<<trigTowColl->at(i)->adc().at(m_distance_odd[i]-3)<<"<="<<v_low_t<<std::endl;
								}
							}
						}
					}			
					

					else{
					
							if(trigTowColl->at(i)->adc().at(m_distance_odd[i]-1)<=v_high_t){

								if(m_distance_odd[i]+4==central){
									for (int t = 0 ; t < 4 ; t++ ){
										result[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
									}
									for(int t=0 ; t<3 ; t++){
										logic[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
									}
								}
								else{
									std::cout<<i<<"exp="<<central-4<<" data="<<m_distance_odd[i]<<" branch="<<"3 "<<trigTowColl->at(i)->adc().at(m_distance_odd[i]-2)<<" <= "<<v_high_t<<" "<<trigTowColl->at(i)->adc().at(m_distance_odd[i]-1)<<"<="<<v_high_t<<std::endl;
								}

							}
					
							else {

								if(m_distance_odd[i]+2==central){
									for (int t = 0 ; t < 4 ; t++ ){
										result[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
									}
									for(int t=0 ; t<2 ; t++){
										logic[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
									}
								}
								else{
									std::cout<<i<<"exp="<<central-2<<" data="<<m_distance_odd[i]<<" branch="<<"4 "<<trigTowColl->at(i)->adc().at(m_distance_odd[i]-2)<<" <= "<<v_high_t<<" "<<trigTowColl->at(i)->adc().at(m_distance_odd[i]-1)<<">"<<v_high_t<<std::endl;
								}						
							}
						}					
					
				}
				if (m_distance_odd[i]==7 && branch!=1 ){
					logic_wrong[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
				}
				if (m_distance_odd[i]==5 && branch!=2 ){
					for(unsigned int g=0;g<2;g++){
						logic_wrong[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
					}
				}
				if (m_distance_odd[i]==5 && branch!=3 ){
					for(unsigned int g=0;g<2;g++){
						logic_wrong[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
					}
				}
				if (m_distance_odd[i]==3 && branch!=4 ){
					for(unsigned int g=0;g<3;g++){
						logic_wrong[m_step[i]][m_lay]->Fill(trigTowColl->at(i)->eta(),trigTowColl->at(i)->phi());
					}
				}
				m_eta[i]=trigTowColl->at(i)->eta();
				m_phi[i]=trigTowColl->at(i)->phi();
				m_layer[i]=trigTowColl->at(i)->layer();
    			std::string title;
				std::string name;
				std::string path;
				std::stringstream ss;
				ss<< std::hex<<trigTowColl->at(i)->coolId();
				std::string res(ss.str());
				title = "C.Curve for each Trigger Tower 0x"+res;
				calibration[i]->SetTitle(title.c_str());
				calibration[i]->GetXaxis()->SetTitle("Event");
				calibration[i]->GetYaxis()->SetTitle("ADCs count");
				title = "C.Curve for each Trigger Tower "+std::to_string(trigTowColl->at(i)->coolId());
				calibration2[i]->SetTitle(title.c_str());
				calibration2[i]->GetXaxis()->SetTitle("ET [GeV]");
				calibration2[i]->GetYaxis()->SetTitle("ADCs count");

				name = "Spectrum_0_"+std::to_string(i)+" eta = "+std::to_string(trigTowColl->at(i)->eta())+"_phi = "+std::to_string(trigTowColl->at(i)->phi());
				title = "Spectrum_0_"+std::to_string(i)+" for each Trigger Tower 0x"+res;
				path = "/file1/spectrum_0/"+std::to_string(trigTowColl->at(i)->eta())+"/"+name;
				CHECK(histSvc->regHist(path.c_str(),spectrum_0[i]));
				spectrum_0[i]->SetTitle(title.c_str());
				spectrum_0[i]->SetName(name.c_str());
				spectrum_0[i]->GetXaxis()->SetTitle("ET [GeV]");

				name = "Spectrum_1_"+std::to_string(i)+" eta = "+std::to_string(trigTowColl->at(i)->eta())+"_phi = "+std::to_string(trigTowColl->at(i)->phi());
				title = "Spectrum_1_"+std::to_string(i)+" for each Trigger Tower 0x"+res;
				path = "/file1/spectrum_1/"+std::to_string(trigTowColl->at(i)->eta())+"/"+name;
				CHECK(histSvc->regHist(path.c_str(),spectrum_1[i]));
				spectrum_1[i]->SetTitle(title.c_str());
				spectrum_1[i]->SetName(name.c_str());
				spectrum_1[i]->GetXaxis()->SetTitle("ET [GeV]");
				if(m_lay==0){/*
				for (int w=0;w<15;w++){
					name = "ADC_"+std::to_string(w)+"eta="+std::to_string(trigTowColl->at(i)->eta())+"_phi="+std::to_string(trigTowColl->at(i)->phi());
					title = "ADC_"+std::to_string(w)+" for each Trigger Tower 0x"+res;
					path = "/file1/ADChisto/"+std::to_string(trigTowColl->at(i)->eta())+"/"+name;
					CHECK(histSvc->regHist(path.c_str(),ADChisto[i][w]));
					ADChisto[i][w]->SetTitle(title.c_str());
					ADChisto[i][w]->SetName(name.c_str());
					ADChisto[i][w]->GetXaxis()->SetTitle("ET [GeV]");
				}
				*/
				}
				/*
				for(int t=0;t<15; t++){
					for(int d=0;d<64;d++){
						if (trigTowColl->at(i)->eta()==etaslice[d]){
							TH2Feta[d][t]->Add(ADChisto[i][t]);
						}
					}
				}
				*/
				if(i==7167){
					for(int d=0;d<66;d++){
						for(int t=0;t<15; t++){
							std::cout<<i<<" "<<t<<" "<<d<<std::endl;
							name = "ADC_"+std::to_string(t)+"eta="+std::to_string(etaslice[d]);
							title = "ADC_"+std::to_string(t)+" eta = "+std::to_string(etaslice[d]);
							path = "/file1/etaslice/"+std::to_string(etaslice[d])+"/"+name;
							CHECK(histSvc->regHist(path.c_str(),TH2Feta[d][t]));
							TH2Feta[d][t]->SetTitle(title.c_str());
							TH2Feta[d][t]->SetName(name.c_str());
							TH2Feta[d][t]->GetXaxis()->SetTitle("ET [GeV]");
						}
					}
				}
				//title = "Peak Position versus Adc Number tt_0x"+res;
				//peak[i]->SetTitle(title.c_str());
				title = "Maximum Adc Position versus Maximum Adc Value tt_0x"+res;
				mvsm[i]->SetTitle(title.c_str());
				title = " Peak Finder "+res;
				peakFinder[i]->SetTitle(title.c_str());
				peakFinder[i]->GetXaxis()->SetTitle("ET [GeV]");
				title = "Saturation 0x"+res;
				saturation[i]->SetTitle(title.c_str());
				saturation[i]->GetXaxis()->SetTitle("ET [GeV]");
				title = "PSE 0x"+res;
				PSE[i]->SetTitle(title.c_str());
				PSE[i]->GetYaxis()->SetTitle("PSE");
				PSE[i]->GetXaxis()->SetTitle("ET [GeV]");
				
				title = "Correlation plot Et vs adc Peak 0x"+res;
				corrETvsPeak[i]->SetTitle(title.c_str());
				corrETvsPeak[i]->GetXaxis()->SetTitle("ET [GeV]");
				corrETvsPeak[i]->GetYaxis()->SetTitle("ADC_{peak}");
				/*
				for (unsigned j=0;j<5;j++){
				  
					title = "TH2F Histograms tt_0x"+res;
					TH2Fhisto[i][j]->SetTitle(title.c_str());
					
					title = "TH2F cross check Histograms tt_"+std::to_string(trigTowColl->at(i)->coolId());
					TH2Fcheck[i][j]->SetTitle(title.c_str());
					title = "TH2F cross check2 Histograms tt_"+std::to_string(trigTowColl->at(i)->coolId());
					TH2Fcheck2[i][j]->SetTitle(title.c_str());
				
				}
				*/
				}//close the if on the last event


						
			}//close the if on the event !=0
			
	
		}//broken trigger tower

	}//close the loop over the trigger towets


  return StatusCode::SUCCESS;
}












//====================================================================================
//==================================***************===================================
//==================================* USEFUL CODE *===================================
//==================================***************===================================
//====================================================================================



//================================================================================
//for (const auto* tt : *trigTowColl){
//	static xAOD::TriggerTower::ConstAccessor<float> caloEtAccessor("CaloCellET");
//	float caloET = caloEtAccessor(*tt);

//std::cout << caloET << std::endl;

//}












/*			
			pulse[7] = m_max[i];		
			TH2Fcheck2[i][7]->Fill(m_max[i],m_max[i]);
			
			for ( int j = 1; j < 8; j++){
					
					if ((m_maxpos[i])+j<15){
						pulse[7+j]=(trigTowColl->at(i)->adc()).at(m_maxpos[i]+j);
						TH2Fcheck2[i][7+j]->Fill(m_max[i],(trigTowColl->at(i)->adc()).at(m_maxpos[i]+j));
						}
					else {
						TH2Fcheck2[i][7+j]->Fill(m_max[i],30);
						pulse[7+j]=30;	
					}

					if (m_maxpos[i]-j>=0){
						pulse[7-j]=(trigTowColl->at(i)->adc()).at(m_maxpos[i]-j);
						TH2Fcheck2[i][7-j]->Fill(m_max[i],(trigTowColl->at(i)->adc()).at(m_maxpos[i]-j));
						}
					else {
						TH2Fcheck2[i][7-j]->Fill(m_max[i],30);	
						pulse[7-j]=30;
					}
					

				}
			*/
			//I want to exclude the broken tt from the final count, I added also the normalization for the energy
			/*
			for(unsigned int j=0;j<(trigTowColl->at(i)->adc()).size();j++){
					//to see the new shape
					if (m_max[i]>45){		
						profile[eventInfo->eventNumber()]->Fill(j,(trigTowColl->at(i)->adc()).at(j)/caloET[i]);
					}
			}
			
			
			//to see the new shape 
			
			if (i==1){
				for(unsigned int j=0;j<(trigTowColl->at(1)->adc()).size();j++){
						//to see the new shape
					for (unsigned int l=0;l<pulse[j];l++){		
							pulseNewShape[eventInfo->eventNumber()]->Fill(j);
						}	
					
					}
				
			
				}
			*/











			//is a way to exclude saturated towers
			//if(m_sat[i]<2){
			//	peak[i]->Fill(m_maxpos[i]);
			//}















			/*
			if(*events_step[i][m_step[i]+m_lay*15]>2){
				
				*mean[i][m_step[i]+m_lay*15] = Calc[i][m_step[i]+m_lay*15]->GetMean();
				*sigma[i][m_step[i]+m_lay*15] = Calc[i][m_step[i]+m_lay*15]->GetRMS();
				if (i==140){
					s+td::cout<<*mean[i][m_step[i]+m_lay*15]<<std::endl;
					std::cout<<*sigma[i][m_step[i]+m_lay*15]<<std::endl;
				}
			}
			*/
			//if ( *events_step[i][m_step[i]+m_lay*15]<60 or caloET[i]<*mean[i][m_step[i]+m_lay*15] +*sigma[i][m_step[i]+m_lay*15]*3){









			//create vector containg coll id and  thresholds
/*
std::string line;
int j=0;
int cont=0;
std::ifstream f1("Ppr_test");

std::ofstream f2("numb");

while ( f1.good() ){
    j++;
    x[0][j] = new std::string;
    x[1][j] = new std::string;
    x[2][j] = new std::string;

    int dim=0;
    getline( f1 , line );
    cont=0;
    for( std::string::iterator it = line.begin(); it!=line.end() ; it++){
      	dim ++;
    }
    
    for (int i=1; i<dim-1; i++){   
    int t=0;   
      	if (line[i]==',' && line[i-1]=='b'){
			for (int t=0;t<10;t++){
	  			*(x[0][j])+=line[i+1+t] ;
			}	 
      	}
      	t=0;
      	if (line[i]==':' && line[i-1]=='t' && cont ==1){
			while (line[i+1+t]!=','){
	  			*(x[2][j])+=line[i+1+t] ;
	  			t++;
			}
			cont++;
      	}
      	t=0;
    	if (line[i]==':' && line[i-1]=='t' && cont==0){
			while (line[i+1+t]!=','){
	  			*(x[1][j])+=line[i+1+t] ;
				t++;
			} 
		cont=1;
      	}
    }
    std::cout <<*(x[0][j])<< " "<<*(x[1][j]) <<" "<<*(x[2][j]) <<std::endl;  
}
f1.close();
f2.close();

int t_high,t_low;
string coolid;
coolid = to_string(trigTowColl->at(i)->coolId());
for (int g=0 ; g < 8193 ; g++){
    if(collid==x[0][g]){
      	t_low=stoi(x[1][g]);
      	t_high=stoi(x[2][g]);
      	cout<<"low thershold: "<<t_low<<"  high threshold: "<<t_high<<endl;
	}
}
*/
//=================================================================================


