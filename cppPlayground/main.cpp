
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

class resultSet {
public:
	vd freq;
	
	vd Vout;
	vd Vin;
	
	vd dY1;
	vd dY2;
};
int main(int argc, const char * argv[]) {
	
	bool debug = false;
	
	double gains[7];
	resultSet exp1 = resultSet();
	resultSet exp2 = resultSet();
	vector<resultSet> exp;
	
	
	exp1.freq = {
		50,
		97,
		250,
		482,
		1000,
		2000,
		2400
	};
	
	exp1.Vout = {
		0.936,
		1.78,
		4.12,
		6.48,
		8.16,
		8.96,
		8.96
	};
	exp1.Vin = {
		9.44,
		9.44,
		9.28,
		9.28,
		9.28,
		9.44,
		9.44
	};
	
	exp1.dY1 = {
		1,
		0.2,
		0.3,
		0.3,
		0.2,
		0.1,
		0.1
	};
	
	exp1.dY2 = {
		4,
		2,
		4,
		4,
		5,
		5,
		4
	};
	
	exp2.freq = {
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
	
	exp2.Vout = {
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
	exp2.Vin = {
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
	
	
	exp2.dY1 = {
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
	
	exp2.dY2 = {
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

	exp = {
		exp1,
		exp2
	};
	
	cout << "\n\nTHEORETICAL RESULTS:\n\n";
	
	cout << "experiment 1\n\n";
	
	for(int i=0;i< exp1.freq.size(); ++i) {
		double w = 2 * pi * exp1.freq[i];
		double RC = 33.f / 100000;
		double re = pow(w,2)/(pow(w, 2)+pow(1/RC,2));
		double im = (w/RC) / (pow(w, 2) + pow(1/RC,2));
		double mag = sqrt(pow(re, 2) + pow(im, 2));
		double phase = atan(im/re) * 180 / pi;
		if(debug) {
			printf("%.0fHz input frequency:\n",exp1.freq[i]);
			printf("w=%f\tRC=%f\tre=%f\tim=%f\tmag=%f\tphase=%f\n\n",w,RC,re,im,mag,phase);
		} else {
			printf("%.0fHz input frequency:\n",exp1.freq[i]);
			//			printf("H(jw)=%.3f\\;+\\:j%.3f\n",re,im);
			//			printf("\\left|H(jw)\\right|=%.3f\n",mag);
			//			printf("phase=\\;%.3f\n",phase);
			printf("H(jw)\\;=\\frac{w^2}{w^2+({\\displaystyle\\frac1{RC}})^2}+\\;j\\times\\frac{w^2}{RC(w^2+({\\displaystyle\\frac1{RC}})^2)}=%.3f\\;+\\:j%.3f\n", re,im);
			printf("\\left|H(jw)\\right|\\;=\\;\\sqrt{Re(H)^2+Im(H)^2}=\\sqrt{%.3f^2+%.3f^2}=%.3f\n",re,im,mag);
			printf("phase\\;=\\;\\tan^{-1}\\left(\\frac{Im(H)}{Re(H)}\\right)\\;=\\;\\tan^{-1}(\\frac {%.3f}{%.3f})\\;=\\;%.3f^\\circ\n",im,re,phase);
		}
		cout << "\n\n";
	}
	
	
	
	
	
	cout << "experiment 2\n\n";
	
	for(int i=0;i<exp2.freq.size(); ++i) {
		double w = 2 * pi * exp2.freq[i];
		double RL = 10000;
		double re = pow(RL, 2)/(pow(w, 2) + pow(RL, 2));
		double im = w * RL /(pow(w, 2) + pow(RL, 2));
		double mag = sqrt(pow(re, 2) + pow(im, 2));
		double phase = atan(im/re) * 180 / pi;
		if(debug) {
			printf("%.0fHz input frequency:\n",exp2.freq[i]);
			printf("w=%f\tR/L=%f\tre=%f\tim=%f\tmag=%f\tphase=%f\n\n",w,RL,re,im,mag,phase);
		} else {
			printf("%.0fHz input frequency:\n",exp2.freq[i]);
			printf("H(jw)\\;=\\;\\frac{({\\displaystyle\\frac RL})^2}{w^2\\;+\\;({\\displaystyle\\frac RL})^2}\\;+\\;j\\times\\frac{w\\times({\\displaystyle\\frac RL})}{w^2+({\\displaystyle\\frac RL})^2}\\;=\\;%.3f\\;+\\;j%.3f\n", re,im);
			printf("\\left|H(jw)\\right|\\;=\\;\\sqrt{Re(H)^2+Im(H)^2}=\\sqrt{%.3f^2+%.3f^2}=%.3f\n",re,im,mag);
			printf("phase\\;=\\;\\tan^{-1}\\left(\\frac{Im(H)}{Re(H)}\\right)\\;=\\;\\tan^{-1}(\\frac {%.3f}{%.3f})\\;=\\;%.3f^\\circ\n",im,re,phase);
		}
		cout << "\n\n";
	}
	
	
	cout << "\nEXPERIMENTAL RESULTS:\n\n";
	
	
	
	for(int e=0; e<exp.size(); ++e) {
		cout << " ======= GAINS =======\n";
		vd freq = exp[e].freq;
		vd Vout = exp[e].Vout;
		vd Vin = exp[e].Vin;
		vd dY1 = exp[e].dY1;
		vd dY2 = exp[e].dY2;
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
	}
	
	
	cout << endl;
	cout.flush();
	return 0;
}
