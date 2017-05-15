
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
	// controlled
	vd freq;
	
	// observed
	vd Vout;
	vd Vin;
	
	vd dY1;
	vd dY2;
	
	// calculated
	vd phase;
	vd gain;
	vd phaseExp;
	vd gainExp;
};
int main(int argc, const char * argv[]) {
	
	bool debug = false;
	
	double gains[7];
	resultSet exp1 = resultSet();
	resultSet exp2a = resultSet();
	resultSet exp2b = resultSet();
	resultSet exp3 = resultSet();
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
	
	exp2a.freq = {
		150,
		318,
		1000,
		1600,
		5000,
		7900,
		10000
	};
	
	exp2a.Vout = {
		4.4,
		4.6,
		4.6,
		4.28,
		3,
		2.18,
		1.8
	};
	
	exp2a.Vin = {
		9.52,
		10.2,
		10.4,
		10.0,
		10.0,
		10.0,
		10.0
	};
	
	exp2a.dY1 = {
		0.05,
		0,
		0.1,
		0.2,
		0.3,
		0.25,
		0.2
	};
	
	exp2a.dY2 = {
		6.5,
		3,
		5,
		6,
		4,
		2.5,
		2
	};
	
	exp2b.freq = {
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
	
	exp2b.Vout = {
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
	exp2b.Vin = {
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
	
	
	exp2b.dY1 = {
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
	
	exp2b.dY2 = {
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

	
	
	exp3.freq = {
		300,
		335,
		1510,
		1600,
		1670,
		7500,
		8300
	};
	
	exp3.Vout = {
		1.15,
		1.11,
		1.04,
		1.01,
		1.01,
		0.392,
		0.384
	};
	exp3.Vin = {
		10.2,
		10.1,
		9.92,
		9.92,
		10.2,
		9.84,
		9.84
	};
	
	exp3.dY1 = {
		0.1,
		0.1,
		0.15,
		0.15,
		0.15,
		0.15,
		0.1
	};
	
	exp3.dY2 = {
		6.5,
		6,
		3,
		3,
		3,
		2.5,
		2.5
	};
	
	
	exp = {
		exp1,
		exp2a,
		exp2b,
		exp3
	};
	
	for(int i=0; i<exp.size(); ++i) {
		exp[i].gain.resize(exp[i].freq.size());
		exp[i].gainExp.resize(exp[i].freq.size());
		exp[i].phase.resize(exp[i].freq.size());
		exp[i].phaseExp.resize(exp[i].freq.size());
	}
	
	cout << "\n\nTHEORETICAL RESULTS:\n\n";
	
	cout << "experiment 1\n\n";
	
	for(int i=0;i< exp1.freq.size(); ++i) {
		double w = 2 * pi * exp1.freq[i];
		double RC = 33.f / 100000;
		double re = pow(w,2)/(pow(w, 2)+pow(1/RC,2));
		double im = (w/RC) / (pow(w, 2) + pow(1/RC,2));
		double mag = sqrt(pow(re, 2) + pow(im, 2));
		double phase = atan(im/re) * 180 / pi;
		exp[0].gain[i] = mag;
		exp[0].phase[i] = phase;
		if(debug) {
			printf("%.0fHz input frequency:\n",exp1.freq[i]);
			printf("w=%f\tRC=%f\tre=%f\tim=%f\tmag=%f\tphase=%f\n\n",w,RC,re,im,mag,phase);
		} else {
			printf("%.0fHz input frequency:\n",exp1.freq[i]);
			//			printf("H(jw)=%.3f\\;+\\:j%.3f\n",re,im);
			//			printf("\\left|H(jw)\\right|=%.3f\n",mag);
			//			printf("phase=\\;%.3f\n",phase);
			printf("H(jw)\\;=\\frac{w^2}{w^2+({\\displaystyle\\frac1{RC}})^2}+\\;j\\times\\frac{w^2}{RC(w^2+({\\displaystyle\\frac1{RC}})^2)}=%.3f\\;+\\:j(%.3f)\n", re,im);
			printf("\\left|H(jw)\\right|\\;=\\;\\sqrt{Re(H)^2+Im(H)^2}=\\sqrt{%.3f^2+%.3f^2}=%.3f\n",re,im,mag);
			printf("phase\\;=\\;\\tan^{-1}\\left(\\frac{Im(H)}{Re(H)}\\right)\\;=\\;\\tan^{-1}(\\frac {%.3f}{%.3f})\\;=\\;%.3f^\\circ\n",im,re,phase);
		}
		cout << "\n\n";
	}
	
	
	
	
	
	cout << "experiment 2a\n\n";
	
	for(int i=0;i<exp2a.freq.size(); ++i) {
		double w = 2 * pi * exp2a.freq[i];
		double RL = 10000;
		double re = pow(RL, 2)/(pow(w, 2) + pow(RL, 2));
		double im = - w * RL /(pow(w, 2) + pow(RL, 2));
		double mag = sqrt(pow(re, 2) + pow(im, 2));
		double phase = atan(im/re) * 180 / pi;
		exp[1].gain[i] = mag;
		exp[1].phase[i] = phase;
		if(debug) {
			printf("%.0fHz input frequency:\n",exp2a.freq[i]);
			printf("w=%f\tR/L=%f\tre=%f\tim=%f\tmag=%f\tphase=%f\n\n",w,RL,re,im,mag,phase);
		} else {
			printf("%.0fHz input frequency:\n",exp2a.freq[i]);
			printf("H(jw)\\;=\\;\\frac{({\\displaystyle\\frac RL})^2}{w^2\\;+\\;({\\displaystyle\\frac RL})^2}\\;+\\;j\\times\\frac{w\\times({\\displaystyle\\frac RL})}{w^2+({\\displaystyle\\frac RL})^2}\\;=\\;%.3f\\;+\\;j(%.3f)\n", re,im);
			printf("\\left|H(jw)\\right|\\;=\\;\\sqrt{Re(H)^2+Im(H)^2}=\\sqrt{%.3f^2+%.3f^2}=%.3f\n",re,im,mag);
			printf("phase\\;=\\;\\tan^{-1}\\left(\\frac{Im(H)}{Re(H)}\\right)\\;=\\;\\tan^{-1}(\\frac {%.3f}{%.3f})\\;=\\;%.3f^\\circ\n",im,re,phase);
		}
		cout << "\n\n";
	}
	
	
	cout << "experiment 2b\n\n";
	
	for(int i=0;i<exp2b.freq.size(); ++i) {
		double R1 = 10, R2 = 33000;
		double L = 0.001;
		double C = 0.01 * pow(10, -6);
		double w = 2 * pi * exp2b.freq[i];
		double A = (C*R1*R2 + L)/(L*C*R2);
		double B = (R1 - pow(w, 2)*C*R2*L)/(C*R2*L);
		
		double re = pow(w, 2)*(R1/L)*A/(pow(w, 2)*pow(A, 2)+pow(B, 2));
		double im = w*R1/L*B/(pow(w, 2)*pow(A, 2)+pow(B, 2));
		double mag = sqrt(pow(re, 2) + pow(im, 2));
		double phase = atan(im/re) * 180 / pi;
		exp[2].gain[i] = mag;
		exp[2].phase[i] = phase;
		if(debug) {
			printf("%.0fHz input frequency:\n",exp2b.freq[i]);
			printf("w=%f\tre=%f\tim=%f\tmag=%f\tphase=%f\n\n",w,re,im,mag,phase);
		} else {
			printf("%.0fHz input frequency:\n",exp2b.freq[i]);
			printf("H(jw)\\;=%.3f\\;+\\:j(%.3f)\n", re,im);
			printf("\\left|H(jw)\\right|\\;=\\;\\sqrt{Re(H)^2+Im(H)^2}=\\sqrt{%.3f^2+%.3f^2}=%.3f\n",re,im,mag);
			printf("phase\\;=\\;\\tan^{-1}\\left(\\frac{Im(H)}{Re(H)}\\right)\\;=\\;\\tan^{-1}(\\frac {%.3f}{%.3f})\\;=\\;%.3f^\\circ\n",im,re,phase);
		}
		cout << "\n\n";
	}
	
	cout << "experiment 3\n\n";
	
	for(int i=0;i<exp3.freq.size(); ++i) {
		double w = 2 * pi * exp3.freq[i];
		double A = -pow(w, 2) + pow(10, 8);
		double RC = 0.001;
		double re = pow(w / RC, 2) / (pow(w / RC, 2)+ pow(A, 2));
		double im = w * A / RC / (pow(w / RC, 2) + pow(A, 2));
		double mag = sqrt(pow(re, 2) + pow(im, 2));
		double phase = atan(im/re) * 180 / pi;
		exp[3].gain[i] = mag;
		exp[3].phase[i] = phase;
		if(debug) {
			printf("%.0fHz input frequency:\n",exp3.freq[i]);
			printf("w=%f\tre=%f\tim=%f\tmag=%f\tphase=%f\n\n",w,re,im,mag,phase);
		} else {
			printf("%.0fHz input frequency:\n",exp3.freq[i]);
			printf("H(jw)\\;=%.3f\\;+\\:j(%.3f)\n", re,im);
			printf("\\left|H(jw)\\right|\\;=\\;\\sqrt{Re(H)^2+Im(H)^2}=\\sqrt{%.3f^2+%.3f^2}=%.3f\n",re,im,mag);
			printf("phase\\;=\\;\\tan^{-1}\\left(\\frac{Im(H)}{Re(H)}\\right)\\;=\\;\\tan^{-1}(\\frac {%.3f}{%.3f})\\;=\\;%.3f^\\circ\n",im,re,phase);
		}
		cout << "\n\n";
	}


	cout << "\nEXPERIMENTAL RESULTS:\n\n";
	
	
	
	for(int e=0; e<exp.size(); ++e) {
		printf("experiment %i:\n\n",e);
		cout << " ======= GAINS =======\n";
		vd freq = exp[e].freq;
		vd Vout = exp[e].Vout;
		vd Vin = exp[e].Vin;
		vd dY1 = exp[e].dY1;
		vd dY2 = exp[e].dY2;
		
		for(int i=0; i<freq.size(); ++i) {
			gains[i] = Vout[i]/Vin[i];
			exp[e].gainExp[i] = gains[i];
			printf("%.0fHz input frequency:\nGain\\;=\\;\\frac{V_{out}}{V_{in}}=\\frac{%.3f}{%.3f}=%.3f\n",freq[i],Vout[i],Vin[i],gains[i]);
		}
		
		cout << "\n\n\n";
		cout << " ==== GAINS in db ====\n";
		
		for(int i=0; i<freq.size(); ++i) {
			printf("%.0fHz input frequency:\nGain(db)\\;=\\;20\\log(%.3f)=%.3f\n\n",freq[i], gains[i], 20 * log10(gains[i]));
		}
		
		
		
		
		
		cout << "\n\n\n";
		cout << " ==== PHASES ====\n";
		
		for(int i=0; i<freq.size(); ++i) {
			double phase = (dY1[i] >= 1.0 ? dY1[i] : dY1[i] * 2) / dY2[i] * 360;
			exp[e].phaseExp[i] = phase;
			printf("%.0fHz input frequency:\nPhase\\;=\\frac{%.1f}{%.1f}\\times360=%.1f\n\n",freq[i],(dY1[i] >= 1.0 ? /* 5 per div this is easier*/ dY1[i] : dY1[i] * 2),dY2[i], phase);
		}
	}
	
	
	cout << "========= COMPARISON TABLES =========\n\n";
	
	for(int e=0; e<exp.size(); ++e){
		printf("experiment %i:\n\n", e + 1);
		printf("Theoretical:\n\n");
		printf("%-20s%-20s%-20s%-20s%-20s%-20s\n","Frequency","Vin", "Vout", "Phase(Vout)", "Gain", "Gain(db)");
		for(int i=0; i<exp[e].freq.size(); ++i){
			printf("%-20.0f%-20.1f%-20.1f%-20.2f%-20.3f%-20.3f\n", exp[e].freq[i], 10.f,exp[e].gain[i] * 10, exp[e].phase[i], exp[e].gain[i], 20*log10(exp[e].gain[i]));
		}
		printf("\n\nExperimental:\n\n");
		printf("%-20s%-20s%-20s%-20s%-20s\n","Frequency","Vin", "Vout", "Phase(Vout)", "Gain", "Gain(db)");
		for(int i=0; i<exp[e].freq.size(); ++i){
			printf("%-20.0f%-20.1f%-20.1f%-20.2f%-20.3f%-20.3f\n",exp[e].freq[i],exp[e].Vin[i], exp[e].Vout[i], exp[e].phaseExp[i], exp[e].gainExp[i], 20*log10(exp[e].gainExp[i]));
		}
		cout << "\n\n";
	}
	
	
	
	cout << endl;
	cout.flush();
	return 0;
}
