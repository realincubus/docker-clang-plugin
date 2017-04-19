#include <iostream>
#include <fstream>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <vector>
//#include <typeinfo>
using namespace std;
const double lambda=632e-9; //wellenlaenge
const double d=.8, n=1.33, R=1.65e-03, xmax=.4, ps=1e-06;
const int dphi=100000, dtheta=100000, dp=10000000, dx=1000;
double schirm[dx];
double ethetar[dtheta], ethetai[dtheta], epr[dp], epi[dp];


int main(void){
	
	
	//define outputfiles
	ofstream outputSchirm("schirm.dat");
	ofstream outputRand("tropfen.dat");
	ofstream outputPartikel("partikel.dat");
	ofstream outputData("startbedingungen.dat");

	if(outputSchirm.fail()){
		cout << "output file schirm.dat cannot be created";
		return 99;	
	}
	if(outputRand.fail()){
		cout << "output file tropfen.dat cannot be created";
		return 99;	
	}
	if(outputData.fail()){
		cout << "output file startbedignung.dat cannot be created";
		return 99;	
	}
	if(outputPartikel.fail()){
		cout << "output file partikel.dat cannot be created";
		return 99;	
	}
	clock_t timer;
	timer=clock();
	

	//Geometrische Grenze für gtheta
	double gtheta=1.5;//2.*asin(1./n)-M_PI/2.;

	//Summierung in Partikelebene

	//untere haelfte
	#pragma acc parallel  loop independent copyout(epr[0:dp], epi[0:dp])
	for(int i=0; i<dp/2; i++){
		double sumr=0;
		double sumi=0;
		double p=2.*i/dp*(-R+ps)-ps; //[-R:-ps]
		for(int j=0; j<dphi; j++){
			double phi=3.1/dphi*j-3.1/2;
			//double Eq=(phi!=0)?sin(phi*4)/(4*phi):1;
			double r1=sqrt(R*R+p*p-2*p*R*sin(phi));
			double phase=2.*M_PI/lambda*(n*r1);
			double phase2=2.*M_PI/lambda*(R*cos(phi)); //Tropfeneingang
			double cosa=1./sqrt(	1+(p-R*sin(phi))*(p-R*sin(phi))/(R*R*cos(phi)*cos(phi))	);
			double real1=exp(-sin(phi)*sin(phi)/.1)*cos(phase2); //Tropfeneinang
			double real2=cosa/r1*cos(phase); //Rückseite
			double imag1=exp(-sin(phi)*sin(phi)/.1)*sin(phase2);
			double imag2=cosa/r1*sin(phase);
			sumr+=real1*real2-imag1*imag2;
			sumi+=real1*imag2+real2*imag1;
			//cout << cosa << endl;
		}
		epr[i]=sumr;
		epi[i]=sumi;
	}
	//obere haelfte ist auf Grund der Symmetrie identisch

	for(int i=0; i<dp/2; i++){
		outputPartikel << 2.*i/dp*(-R+ps)-ps << "\t" << abs(epr[i]*epr[i]+epi[i]*epi[i]) << endl;
	}


	//Summierung auf Tropfenrand
	#pragma acc parallel  loop independent copyin(epi[0:dp], epr[0:dp]) copyout(ethetar[0:dtheta], ethetai[0:dtheta])
	for(int i=0; i<dtheta; i++){
		double theta=2.*gtheta/dtheta*i-gtheta;
		double sumr=0;
		double sumi=0;
		for(int j=0; j<dp/2; j++){
			double p=2.*j/dp*(-R+ps)-ps;
			//double Eq=(phi!=0)?sin(phi*4)/(4*phi):1;
			double r1=sqrt(R*R+p*p-2.*p*R*sin(theta));
			double phase=2.*M_PI/lambda*(n*r1);
			double cosa=1./sqrt(	1+(p-R*sin(theta))*(p-R*sin(theta))/(R*R*sin(theta)*sin(theta))	);
			double real2=cosa/r1*cos(phase); //Rückseite
			double imag2=cosa/r1*sin(phase);
			double real1=epr[j];
			double imag1=epi[j];
			sumr+=real1*real2-imag1*imag2;
			sumi+=real1*imag2+real2*imag1;
			//cout << cosa << endl;
		}
		for(int j=0; j<dp/2; j++){
			double p=2.*j/dp*(R-ps)+ps;
			double r1=sqrt(R*R+p*p-2.*p*R*sin(theta));
			double phase=2.*M_PI/lambda*(n*r1);
			double cosa=1./sqrt(	1+(p-R*sin(theta))*(p-R*sin(theta))/(R*R*sin(theta)*sin(theta))	);
			double real2=cosa/r1*cos(phase); //Rückseite
			double imag2=cosa/r1*sin(phase);
			double real1=epr[j];
			double imag1=epi[j];
			sumr+=real1*real2-imag1*imag2;
			sumi+=real1*imag2+real2*imag1;
			//cout << cosa << endl;
		}
		ethetar[i]=sumr;
		ethetai[i]=sumi;
		//cout << abs(sumr*sumr+sumi*sumi) << endl;

	}


	for(int i=0; i<dtheta; i++){
		outputRand << 2.*gtheta/dtheta*i-gtheta << "\t" << abs(ethetar[i]*ethetar[i]+ethetai[i]*ethetai[i]) << endl;
	}
	
	//#pragma omp parallel for
	#pragma acc parallel  loop independent copyin(ethetar[0:dtheta], ethetai[0:dtheta]) copyout(schirm[0:dx])
	for(int i=0; i<dx; i++){
		double x=xmax/dx*i;
		double sumr=0;
		double sumi=0;
		
		for(int j=0; j<dtheta; j++){
			double theta=2.*gtheta/dtheta*j-gtheta;
			double r2=sqrt((x-R*sin(theta))*(x-R*sin(theta))+(d+R-R*cos(theta))*(d+R-R*cos(theta)));
			double phase=2.*M_PI/lambda*r2;
			double cosa=1./sqrt(1.+(x-R*sin(theta))*(x-R*sin(theta))/((d+R-R*cos(theta))*(d+R-R*cos(theta))));
			double real1=ethetar[j];
			double real2=cosa/r2*cos(phase);
			double imag1=ethetai[j];
			double imag2=cosa/r2*sin(phase);
			sumr+=real1*real2-imag1*imag2;
			sumi+=real1*imag2+real2*imag1;
		}
		schirm[i]=abs(sumr*sumr+sumi*sumi);
	}

	for(int i=0; i<dx; i++){
		outputSchirm << xmax/dx*i << "\t" << schirm[i] << endl;
	}

	timer=clock()-timer;
	outputData << "Dicke Linse, Kugel, lambda=" << lambda << "\n n=" << n << "\n R=" <<  R <<"\n d=" << d <<  "\n dphi=" << dphi << "\n dtheta=" << dtheta<< endl << " Theta range="<< gtheta <<endl  << " Laufzeit in minuten: " << double(timer)/CLOCKS_PER_SEC/60 << endl;
	

	return 0;
}




