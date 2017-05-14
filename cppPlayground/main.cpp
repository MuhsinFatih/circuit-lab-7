
#include <iostream>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <chrono>
#include <cmath>
#include <fstream>
#include <math.h>
using namespace std;
#include <map>
#define REP(size) for(size_t i=0, length=size; i<length; ++i)
#define REPW(size)  size_t w,length; length=size \
while(w<length)
#define vi  vector<int>
#define vs  vector<string>
#define vd  vector<double>
#define st  size_t
#define pi M_PI
int main(int argc, const char * argv[]) {
	
	bool debug = false;
	
	
	vd freq = {
		50,
		96,
		318,
		482,
		876,
		1600,
		2400,
		8000,
		10000
	};
	
	vd Vout = {
		4.52,
		4.64,
		4.60,
		4.60,
		4.60,
		4.24,
		3.96,
		2.16,
		1.84
	};
	vd Vin = {
		10,
		10.2,
		10.2,
		10.1,
		10.2,
		10.1,
		10,
		10.1,
		10.2
	};
	
	
	vd dY1 = {
		0,
		0,
		0.1,
		0.1,
		0.15,
		0.3,
		0.2,
		0.55,
		0.5
	};
	
	vd dY2 = {
		4,
		5,
		6,
		4,
		5.5,
		6,
		4,
		6,
		5
	};

	double gains[7];
	
	
	
	
	cout << "\nEXPERIMENTAL RESULTS:\n\n";
	
	
	
	cout << " ======= GAINS =======\n";
	
	for(int i=0; i<freq.size(); ++i) {
		gains[i] = Vout[i]/Vin[i];
		printf("%.0fHz input frequency:\nGain\\;=\\;\\frac{V_{out}}{V_{in}}=\\frac{%.3f}{%.3f}=%.3f\n",freq[i],Vout[i],Vin[i],gains[i]);
	}
	
	cout << "\n\n\n";
	cout << " ==== GAINS in db ====\n";
	
	for(int i=0; i<freq.size(); ++i) {
		printf("%.0fHz input frequency:\nGain(db)\\;=\\;20\\log(%.3f)=%.3f\n\n",freq[i], gains[i], 20 * log(gains[i]));
	}
	
	
	
	
	
	
	cout << "\n\n\n";
	cout << " ==== PHASES ====\n";
	
	for(int i=0; i<freq.size(); ++i) {
		printf("%.0fHz input frequency:\nPhase\\;=\\frac{%.1f}{%.1f}\\times360=%.1f\n\n",freq[i],(dY1[i] >= 1.0 ? /* 5 per div this is easier*/ dY1[i] : dY1[i] * 2),dY2[i], (dY1[i] >= 1.0 ? dY1[i] : dY1[i] * 2) / dY2[i] * 360);
	}
	
	
	cout << "\n\nTHEORETICAL RESULTS:\n\n";
	
	cout << "experiment 1\n\n";
	
	for(int i=0;i<freq.size(); ++i) {
		double w = 2 * pi * freq[i];
		double RC = 33.f / 100000;
		double re = pow(w,2)/(pow(w, 2)+pow(1/RC,2));
		double im = (w/RC) / (pow(w, 2) + pow(1/RC,2));
		double mag = sqrt(pow(re, 2) + pow(im, 2));
		double phase = atan(im/re);
		if(debug) {
			printf("%.0fHz input frequency:\n",freq[i]);
			printf("w=%f\tRC=%f\tre=%f\tim=%f\tmag=%f\tphase=%f\n\n",w,RC,re,im,mag,phase);
		} else {
			printf("%.0fHz input frequency:\n",freq[i]);
//			printf("H(jw)=%.3f\\;+\\:j%.3f\n",re,im);
//			printf("\\left|H(jw)\\right|=%.3f\n",mag);
//			printf("phase=\\;%.3f\n",phase);
			printf("H(jw)\\;=\\frac{w^2}{w^2+({\\displaystyle\\frac1{RC}})^2}+\\;j\\times\\frac{w^2}{RC(w^2+({\\displaystyle\\frac1{RC}})^2)}=%.3f\\;+\\:j%.3f\n", re,im);
			printf("\\left|H(jw)\\right|\\;=\\;\\sqrt{Re(H)^2+Im(H)^2}=\\sqrt{%.3f^2+%.3f^2}=%.3f\n",re,im,mag);
			printf("phase\\;=\\;\\tan^{-1}\\left(\\frac{Im(H)}{Re(H)}\\right)\\;=\\;\\tan^{-1}(\\frac {%.3f}{%.3f})\\;=\\;%.3f\n",im,re,phase);
		}
		cout << "\n\n";
	}
	
	freq = {
		50,
		96,
		318,
		482,
		876,
		1600,
		2400,
		8000,
		10000
	};
	
	Vout = {
		4.52,
		4.64,
		4.60,
		4.60,
		4.60,
		4.24,
		3.96,
		2.16,
		1.84
	};
	Vin = {
		10,
		10.2,
		10.2,
		10.1,
		10.2,
		10.1,
		10,
		10.1,
		10.2
	};
	
	
	dY1 = {
		0,
		0,
		0.1,
		0.1,
		0.15,
		0.3,
		0.2,
		0.55,
		0.5
	};
	
	dY2 = {
		4,
		5,
		6,
		4,
		5.5,
		6,
		4,
		6,
		5
	};

	
	
	
	cout << "experiment 2\n\n";
	
	for(int i=0;i<freq.size(); ++i) {
		double w = 2 * pi * freq[i];
		double RL = 10000;
		double re = pow(RL, 2)/(pow(w, 2) + pow(RL, 2));
		double im = w * RL /(pow(w, 2) + pow(RL, 2));
		double mag = sqrt(pow(re, 2) + pow(im, 2));
		double phase = atan(im/re);
		if(debug) {
			printf("%.0fHz input frequency:\n",freq[i]);
			printf("w=%f\tR/L=%f\tre=%f\tim=%f\tmag=%f\tphase=%f\n\n",w,RL,re,im,mag,phase);
		} else {
			printf("%.0fHz input frequency:\n",freq[i]);
			printf("H(jw)\\;=\\;\\frac{({\\displaystyle\\frac RL})^2}{w^2\\;+\\;({\\displaystyle\\frac RL})^2}\\;+\\;j\\times\\frac{w\\times({\\displaystyle\\frac RL})}{w^2+({\\displaystyle\\frac RL})^2}\\;=\\;%.3f\\;+\\;j%.3f\n", re,im);
			printf("\\left|H(jw)\\right|\\;=\\;\\sqrt{Re(H)^2+Im(H)^2}=\\sqrt{%.3f^2+%.3f^2}=%.3f\n",re,im,mag);
			printf("phase\\;=\\;\\tan^{-1}\\left(\\frac{Im(H)}{Re(H)}\\right)\\;=\\;\\tan^{-1}(\\frac {%.3f}{%.3f})\\;=\\;%.3f\n",im,re,phase);
		}
		cout << "\n\n";
	}
	
	
	cout << endl;
	return 0;
}
